/*
 * Copyright 2019-present Open Networking Foundation
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

#include "gRPCServerImpl-CellConfigReport.h"

gRPCServerImplCellConfigReport::gRPCServerImplCellConfigReport() {}

gRPCServerImplCellConfigReport::gRPCServerImplCellConfigReport(AbstractGWCoreComponent* gwCoreComponent) : gwCoreComponent(gwCoreComponent) {}

gRPCServerImplCellConfigReport::gRPCServerImplCellConfigReport(const log_service_t* logSrv, AbstractGWCoreComponent* gwCoreComponent) : logSrv(logSrv), gwCoreComponent(gwCoreComponent) {}

gRPCServerImplCellConfigReport::~gRPCServerImplCellConfigReport() {
    server->Shutdown();
    cq->Shutdown();
}

void
gRPCServerImplCellConfigReport::run() {
    std::string serverInfo = getServerIP() + ":" +  getServerPort();
    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverInfo, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    cq = builder.AddCompletionQueue();
    server = builder.BuildAndStart();
    APIGWLogINFO(this->logSrv, "Server listening on " + serverInfo + " for CellConfigReport");
    handleRPCs();
}

void 
gRPCServerImplCellConfigReport::handleRPCs() {
    new CallData (&service, cq.get(), gwCoreComponent, this->logSrv);
    void* tag;
    bool ok;
    while (true) {
        //GPR_ASSERT(cq->Next(&tag, &ok));
        //GPR_ASSERT(ok);
        cq->Next(&tag, &ok);
        if (!ok) {
            APIGWLogWARN(logSrv, "gRPC server for CellConfigReport is shutting down gracefully");
            break;
        }
        static_cast<CallData*>(tag)->proceed();
    }
}

void
gRPCServerImplCellConfigReport::shutdownGRPCServer() {
    server->Shutdown();
    cq->Shutdown();
}

gRPCServerImplCellConfigReport::CallData::CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent, const log_service_t* logSrv) : AbstractCallData(service, cq), status_(CREATE), gwCoreComponent_(gwCoreComponent), logSrv_(logSrv) {
    proceed();
}

gRPCServerImplCellConfigReport::CallData::CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent) : AbstractCallData(service, cq), status_(CREATE), gwCoreComponent_(gwCoreComponent) {

}

void
gRPCServerImplCellConfigReport::CallData::proceed() {
    if (status_ == CREATE) {
        status_ = PROCESS_UPDATECELLCONFIG;
        service_->RequestUpdateCellConfig(&ctx_, &request_, &responder_, cq_, cq_, this);
    } else if (status_ == PROCESS_UPDATECELLCONFIG) {
        std::stringstream logMsg;
        logMsg << "RIC SB reports received CellConfigReport Message (PLMNID: " << request_.ecgi().plmnid() << ", ECID: " << request_.ecgi().ecid() << ")";

        APIGWLogINFO(logSrv_, logMsg.str().c_str());
        logMsg.str("");
        logMsg << "RIC SB reports received CellConfigReport Message\n* PLMNID: " << request_.ecgi().plmnid() << std::endl;
        logMsg << "* ECID: " << request_.ecgi().ecid() << std::endl;
        logMsg << "* PCI: " << request_.pci() << std::endl;
        for (int index = 0; index < request_.candscells_size(); index++) {
            logMsg << "* Cand-Scells (" << index << ")" << std::endl;
            logMsg << "\t** PCI: " << request_.candscells(index).pci() << std::endl;
            logMsg << "\t** EARFCN DL: " << request_.candscells(index).earfcndl() << std::endl;
        }
        logMsg << "* EARFCN DL: " << request_.earfcndl() << std::endl;
        logMsg << "* EARFCN UL: " << request_.earfcnul() << std::endl;
        logMsg << "* RBS Per TTI DL: " << request_.rbsperttidl() << std::endl;
        logMsg << "* RBS Per TTI UL: " << request_.rbsperttiul() << std::endl;
        logMsg << "* Num TX Antennas: " << request_.numtxantenna() << std::endl;
        logMsg << "* Duplex Mode: " << request_.duplexmode() << std::endl; // 0: fdd, 1: tdd
        logMsg << "* Max Num Connected UEs: " << request_.maxnumconnectedues() << std::endl;
        logMsg << "* Max Num Connected Bearers: " << request_.maxnumconnectedbearers() << std::endl;
        logMsg << "* Max Num UEs Sched Per TTI DL: " << request_.maxnumuesschedperttidl() << std::endl;
        logMsg << "* Max Num UEs Sched Per TTI UL: " << request_.maxnumuesschedperttiul() << std::endl;
        logMsg << "* DLFS Sched Enable: " << request_.dlfsschedenable() << std::endl; // 0: false, 255: true

        APIGWLogDEBUG(logSrv_, logMsg.str().c_str());
        logMsg.str("");

        // Packaging CellConfigReport information to std::map
        std::map<std::string, std::map<std::string, std::string>> message;
        std::map<std::string, std::string> tmpEcgiMap;
        std::map<std::string, std::string> tmpCandScellsMap;
        std::map<std::string, std::string> tmpENBMap;
        
        // ECGI
        tmpEcgiMap[DB_PLMNID_KEY] = request_.ecgi().plmnid();
        tmpEcgiMap[DB_ECID_KEY] = request_.ecgi().ecid();
        message[DB_ECGI_KEY] = tmpEcgiMap;
        
        // CAND-SCELLS
        for (int index = 0; index < request_.candscells_size(); index++) {
            std::stringstream tmpCandScellKey;
            tmpCandScellKey << DB_CAND_SCELL_KEY << ":" << index;
            tmpCandScellsMap[std::to_string(index)] = tmpCandScellKey.str();
            std::map<std::string, std::string> tmpCandScellMap;
            tmpCandScellMap[DB_PCI_KEY] = request_.candscells(index).pci();
            tmpCandScellMap[DB_EARFCN_DL] = request_.candscells(index).earfcndl();
            message[tmpCandScellKey.str()] = tmpCandScellMap;
        }
        message[DB_CAND_SCELLS_KEY] = tmpCandScellsMap;

        // eNB
        tmpENBMap[DB_ECGI_KEY] = DB_ECGI_KEY;
        tmpENBMap[DB_PCI_KEY] = request_.pci();
        tmpENBMap[DB_CAND_SCELLS_KEY] = DB_CAND_SCELLS_KEY;
        tmpENBMap[DB_EARFCN_DL] = request_.earfcndl();
        tmpENBMap[DB_EARFCN_UL] = request_.earfcnul();
        tmpENBMap[DB_RBS_PER_TTI_DL] = request_.rbsperttidl();
        tmpENBMap[DB_RBS_PER_TTI_UL] = request_.rbsperttiul();
        tmpENBMap[DB_NUM_TX_ANTENNAS] = request_.numtxantenna();
        tmpENBMap[DB_DUPLEX_MODE] = request_.duplexmode();
        tmpENBMap[DB_MAX_NUM_CONNECTED_UES] = request_.maxnumconnectedues();
        tmpENBMap[DB_MAX_NUM_CONNECTED_BEARERS] = request_.maxnumconnectedbearers();
        tmpENBMap[DB_MAX_NUM_UES_SCHED_PER_TTI_DL] = request_.maxnumuesschedperttidl();
        tmpENBMap[DB_MAX_NUM_UES_SCHED_PER_TTI_UL] = request_.maxnumuesschedperttiul();
        tmpENBMap[DB_DFLS_SCHED_ENABLE] = request_.dlfsschedenable();
        tmpENBMap[DB_UE_LIST_IN_ENB] = DB_UE_LIST_IN_ENB; // to show UE list - it is not a value in CellConfigReport message
        message[DB_ENB_KEY] = tmpENBMap;

        gwCoreComponent_->notifyEvent(SB_BUNDLE_KEY, REDIS_BUNDLE_KEY, message);
        gwCoreComponent_->notifyEvent(SB_BUNDLE_KEY, ONOS_BUNDLE_KEY, message);
        
        new CallData (service_, cq_, gwCoreComponent_, logSrv_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);
    } else {
        //GPR_ASSERT(status_ == FINISH);
        if (status_ != FINISH) {
            APIGWLogWARN(logSrv_, "gRPC server state machine for CellConfigReport has an error - undefined status");
        }
        delete this;
    }
}

void
gRPCServerImplCellConfigReport::setLogService(const log_service_t* logSrv) {
    this->logSrv = logSrv;
}

void
gRPCServerImplCellConfigReport::setGWCoreComponent(AbstractGWCoreComponent* gwCoreComponent) {
    this->gwCoreComponent = gwCoreComponent;
}

AbstractGWCoreComponent*
gRPCServerImplCellConfigReport::getGWCoreComponent() {
    return gwCoreComponent;
}