/*
 * Copyright 2020-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gRPCServerE2Interface.h"

gRPCServerE2Interface::gRPCServerE2Interface() {}

gRPCServerE2Interface::gRPCServerE2Interface(AbstractGWCoreComponent* gwCoreComponent) : gwCoreComponent(gwCoreComponent) {}

gRPCServerE2Interface::gRPCServerE2Interface(const log_service_t* logSrv, AbstractGWCoreComponent* gwCoreComponent) : logSrv(logSrv), gwCoreComponent(gwCoreComponent) {}

gRPCServerE2Interface::~gRPCServerE2Interface() {
    server->Shutdown();
    cq->Shutdown();
}

void
gRPCServerE2Interface::run() {
    std::string serverInfo = getServerIP() + ":" + getServerPort();
    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverInfo, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    cq = builder.AddCompletionQueue();
    server = builder.BuildAndStart();
    APIGWLogINFO(this->logSrv, "Server listening on " + serverInfo + " for E2-Interface");
    handleRPCs();
}

void
gRPCServerE2Interface::handleRPCs() {
    new CallData (&service, cq.get(), gwCoreComponent, this->logSrv);
    void* tag;
    bool ok;
    while (true) {
        cq->Next(&tag, &ok);
        if (!ok) {
            APIGWLogWARN(logSrv, "gRPC server for E2-Interface is shutting down gracefully");
            break;
        }
        static_cast<CallData*>(tag)->proceed();
    }
}

void
gRPCServerE2Interface::shutdownGRPCServer() {
    server->Shutdown();
    cq->Shutdown();
}

std::string 
gRPCServerE2Interface::getServerIP() {
    return serverIP;
}

void 
gRPCServerE2Interface::setServerIP(std::string serverIP) {
    this->serverIP = serverIP;
}

std::string 
gRPCServerE2Interface::getServerPort() {
    return serverPort;
}

void 
gRPCServerE2Interface::setServerPort(std::string serverPort) {
    this->serverPort = serverPort;
}

void
gRPCServerE2Interface::setLogService(const log_service_t* logSrv) {
    this->logSrv = logSrv;
}

void
gRPCServerE2Interface::setGWCoreComponent(AbstractGWCoreComponent* gwCoreComponent) {
    this->gwCoreComponent = gwCoreComponent;
}

AbstractGWCoreComponent*
gRPCServerE2Interface::getGWCoreComponent() {
    return gwCoreComponent;
}

gRPCServerE2Interface::CallData::CallData(interface::e2::E2InterfaceService::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent, const log_service_t* logSrv) : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), gwCoreComponent_(gwCoreComponent), logSrv_(logSrv) {
    proceed();
}

gRPCServerE2Interface::CallData::CallData(interface::e2::E2InterfaceService::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent) : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), gwCoreComponent_(gwCoreComponent) {
    // To-Do: how to run it without log service?
}

int
gRPCServerE2Interface::CallData::dispatch(interface::e2::E2Message message) {
    if (message.header().messagetype() == interface::e2::E2MessageType::E2_CELLCONFIGREPORT) {
        updateCellConfigReport(message.payload());
    } else if (message.header().messagetype() == interface::e2::E2MessageType::E2_UEADMISSIONSTATUS) {
        updateUEAdmissionStatus(message.payload());
    } else if (message.header().messagetype() == interface::e2::E2MessageType::E2_UECONTEXTUPDATE) {
        updateUEContextUpdate(message.payload());
    } else {
        return 0;
    }
    return 1;
}

void
gRPCServerE2Interface::CallData::updateCellConfigReport(interface::e2::E2MessagePayload payload) {
    // for debuging codes
    // ---
    std::stringstream logMsg;
    logMsg << "RIC SB reports received CellConfigReport Message (PLMNID: " << payload.cellconfigreportattribute().ecgi().plmnid() << ", ECID: " << payload.cellconfigreportattribute().ecgi().ecid() << ")";
    APIGWLogINFO(logSrv_, logMsg.str().c_str());
    logMsg.str("");
    logMsg << "RIC SB reports received CellConfigReport Message\n* PLMNID: " << payload.cellconfigreportattribute().ecgi().plmnid() << std::endl;

    logMsg << "* ECID: " << payload.cellconfigreportattribute().ecgi().ecid() << std::endl;
    logMsg << "* PCI: " << payload.cellconfigreportattribute().pci() << std::endl;
    for (int index = 0; index < payload.cellconfigreportattribute().candscells_size(); index++) {
        logMsg << "* Cand-Scells (" << index << ")" << std::endl;
        logMsg << "\t** PCI: " << payload.cellconfigreportattribute().candscells(index).pci() << std::endl;
        logMsg << "\t** EARFCN DL: " << payload.cellconfigreportattribute().candscells(index).earfcndl() << std::endl;
    }
    logMsg << "* EARFCN DL: " << payload.cellconfigreportattribute().earfcndl() << std::endl;
    logMsg << "* EARFCN UL: " << payload.cellconfigreportattribute().earfcnul() << std::endl;
    logMsg << "* RBS Per TTI DL: " << payload.cellconfigreportattribute().rbsperttidl() << std::endl;
    logMsg << "* RBS Per TTI UL: " << payload.cellconfigreportattribute().rbsperttiul() << std::endl;
    logMsg << "* Num TX Antennas: " << payload.cellconfigreportattribute().numtxantenna() << std::endl;
    logMsg << "* Duplex Mode: " << payload.cellconfigreportattribute().duplexmode() << std::endl; // 0: fdd, 1: tdd
    logMsg << "* Max Num Connected UEs: " << payload.cellconfigreportattribute().maxnumconnectedues() << std::endl;
    logMsg << "* Max Num Connected Bearers: " << payload.cellconfigreportattribute().maxnumconnectedbearers() << std::endl;
    logMsg << "* Max Num UEs Sched Per TTI DL: " << payload.cellconfigreportattribute().maxnumuesschedperttidl() << std::endl;
    logMsg << "* Max Num UEs Sched Per TTI UL: " << payload.cellconfigreportattribute().maxnumuesschedperttiul() << std::endl;
    logMsg << "* DLFS Sched Enable: " << payload.cellconfigreportattribute().dlfsschedenable() << std::endl; // 0: false, 255: true

    APIGWLogDEBUG(logSrv_, logMsg.str().c_str());
    logMsg.str("");
    // ---

    // Packaging CellConfigReport information to std::map
    std::map<std::string, std::map<std::string, std::string>> message;
    std::map<std::string, std::string> tmpEcgiMap;
    std::map<std::string, std::string> tmpCandScellsMap;
    std::map<std::string, std::string> tmpENBMap;

    // ECGI
    tmpEcgiMap[DB_PLMNID_KEY] = payload.cellconfigreportattribute().ecgi().plmnid();
    tmpEcgiMap[DB_ECID_KEY] = payload.cellconfigreportattribute().ecgi().ecid();
    message[DB_ECGI_KEY] = tmpEcgiMap;
    
    // CAND-SCELLS
    for (int index = 0; index < payload.cellconfigreportattribute().candscells_size(); index++) {
        std::stringstream tmpCandScellKey;
        tmpCandScellKey << DB_CAND_SCELL_KEY << ":" << index;
        tmpCandScellsMap[std::to_string(index)] = tmpCandScellKey.str();
        std::map<std::string, std::string> tmpCandScellMap;
        tmpCandScellMap[DB_PCI_KEY] = payload.cellconfigreportattribute().candscells(index).pci();
        tmpCandScellMap[DB_EARFCN_DL] = payload.cellconfigreportattribute().candscells(index).earfcndl();
        message[tmpCandScellKey.str()] = tmpCandScellMap;
    }
    message[DB_CAND_SCELLS_KEY] = tmpCandScellsMap;

    // eNB
    tmpENBMap[DB_ECGI_KEY] = DB_ECGI_KEY;
    tmpENBMap[DB_PCI_KEY] = payload.cellconfigreportattribute().pci();
    tmpENBMap[DB_CAND_SCELLS_KEY] = DB_CAND_SCELLS_KEY;
    tmpENBMap[DB_EARFCN_DL] = payload.cellconfigreportattribute().earfcndl();
    tmpENBMap[DB_EARFCN_UL] = payload.cellconfigreportattribute().earfcnul();
    tmpENBMap[DB_RBS_PER_TTI_DL] = payload.cellconfigreportattribute().rbsperttidl();
    tmpENBMap[DB_RBS_PER_TTI_UL] = payload.cellconfigreportattribute().rbsperttiul();
    tmpENBMap[DB_NUM_TX_ANTENNAS] = payload.cellconfigreportattribute().numtxantenna();
    tmpENBMap[DB_DUPLEX_MODE] = payload.cellconfigreportattribute().duplexmode();
    tmpENBMap[DB_MAX_NUM_CONNECTED_UES] = payload.cellconfigreportattribute().maxnumconnectedues();
    tmpENBMap[DB_MAX_NUM_CONNECTED_BEARERS] = payload.cellconfigreportattribute().maxnumconnectedbearers();
    tmpENBMap[DB_MAX_NUM_UES_SCHED_PER_TTI_DL] = payload.cellconfigreportattribute().maxnumuesschedperttidl();
    tmpENBMap[DB_MAX_NUM_UES_SCHED_PER_TTI_UL] = payload.cellconfigreportattribute().maxnumuesschedperttiul();
    tmpENBMap[DB_DFLS_SCHED_ENABLE] = payload.cellconfigreportattribute().dlfsschedenable();
    tmpENBMap[DB_UE_LIST_IN_ENB] = DB_UE_LIST_IN_ENB; // to show UE list - it is not a value in CellConfigReport message
    message[DB_ENB_KEY] = tmpENBMap;

    gwCoreComponent_->notifyEvent(SB_BUNDLE_CELLCONFIGREPORT_KEY, REDIS_BUNDLE_KEY, message);
}

void
gRPCServerE2Interface::CallData::updateUEAdmissionStatus(interface::e2::E2MessagePayload payload) {
    std::stringstream logMsg;
    logMsg << "RIC SB reports received UEAdmissionStatus Message (C-RNTI: " << payload.ueadmissionstatusattribute().crnti()
        << ", PLMNID: " << payload.ueadmissionstatusattribute().ecgi().plmnid() << ", ECID: " << payload.ueadmissionstatusattribute().ecgi().ecid() << ")";
    APIGWLogINFO(logSrv_, logMsg.str().c_str());

    std::map<std::string, std::map<std::string, std::string>> message;
    std::map<std::string, std::string> tmpEcgiMap;
    std::map<std::string, std::string> tmpUEMap;

    // ECGI
    tmpEcgiMap[DB_PLMNID_KEY] = payload.ueadmissionstatusattribute().ecgi().plmnid();
    tmpEcgiMap[DB_ECID_KEY] = payload.ueadmissionstatusattribute().ecgi().ecid();
    message[DB_ECGI_KEY] = tmpEcgiMap;

    // UE
    tmpUEMap[DB_ECGI_KEY] = DB_ECGI_KEY;
    tmpUEMap[DB_CRNTI_KEY] = payload.ueadmissionstatusattribute().crnti();
    message[DB_UE_KEY] = tmpUEMap;

    gwCoreComponent_->notifyEvent(SB_BUNDLE_UEADMISSIONSTATUS_KEY, REDIS_BUNDLE_KEY, message);
}

void
gRPCServerE2Interface::CallData::updateUEContextUpdate(interface::e2::E2MessagePayload payload) {
    std::stringstream logMsg;
    logMsg << "RIC SB reports received UEContextUpdate Message (IMSI: " << payload.uecontextupdateattribute().imsi() << ", C-RNTI: "
        << payload.uecontextupdateattribute().crnti() << ", PLMNID: " << payload.uecontextupdateattribute().ecgi().plmnid() << ", ECID: " << payload.uecontextupdateattribute().ecgi().ecid()
        << ", MME_UE_S1AP_ID: " << payload.uecontextupdateattribute().mmeues1apid() << ", ENB_UE_S1AP_ID: " << payload.uecontextupdateattribute().enbues1apid() << ")";
    APIGWLogINFO(logSrv_, logMsg.str().c_str());

    std::map<std::string, std::map<std::string, std::string>> message;
    std::map<std::string, std::string> tmpEcgiMap;
    std::map<std::string, std::string> tmpUEMap;

    // ECGI
    tmpEcgiMap[DB_PLMNID_KEY] = payload.uecontextupdateattribute().ecgi().plmnid();
    tmpEcgiMap[DB_ECID_KEY] = payload.uecontextupdateattribute().ecgi().ecid();
    message[DB_ECGI_KEY] = tmpEcgiMap;

    // UE
    tmpUEMap[DB_ECGI_KEY] = DB_ECGI_KEY;
    tmpUEMap[DB_CRNTI_KEY] = payload.uecontextupdateattribute().crnti();
    tmpUEMap[DB_MME_UE_S1AP_ID_KEY] = payload.uecontextupdateattribute().mmeues1apid();
    tmpUEMap[DB_ENB_UE_S1AP_ID_KEY] = payload.uecontextupdateattribute().enbues1apid();
    tmpUEMap[DB_IMSI_KEY] = payload.uecontextupdateattribute().imsi();
    message[DB_UE_KEY] = tmpUEMap;

    gwCoreComponent_->notifyEvent(SB_BUNDLE_UECONTEXTUPDATE_KEY, REDIS_BUNDLE_KEY, message);
}

void
gRPCServerE2Interface::CallData::proceed() {

    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestUpdateAttribute(&ctx_, &request_, &responder_, cq_, cq_, this);
    } else if (status_ == PROCESS) {
        reply_.set_resultcode(dispatch(request_));
        new CallData (service_, cq_, gwCoreComponent_, logSrv_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);
    } else {
        if (status_ != FINISH) {
            APIGWLogWARN(logSrv_, "gRPC server state machine for E2 Interface has an error - undefined status");
        }
        delete this;
    }
}