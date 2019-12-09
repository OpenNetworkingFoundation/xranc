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
    APIGWLogINFO(this->logSrv, "Server listening on " + serverInfo);
    handleRPCs();
}

void 
gRPCServerImplCellConfigReport::handleRPCs() {
    new CallData (&service, cq.get(), this->logSrv);
    void* tag;
    bool ok;
    while (true) {
        //GPR_ASSERT(cq->Next(&tag, &ok));
        //GPR_ASSERT(ok);
        cq->Next(&tag, &ok);
        if (!ok) {
            APIGWLogWARN(logSrv, "gRPC server is shutting down gracefully");
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

gRPCServerImplCellConfigReport::CallData::CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, const log_service_t* logSrv) : AbstractCallData(service, cq), status_(CREATE), logSrv_(logSrv) {
    proceed();
}

gRPCServerImplCellConfigReport::CallData::CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq) : AbstractCallData(service, cq), status_(CREATE) {

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
        logMsg.flush();
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
            logMsg.flush();

        new CallData (service_, cq_, logSrv_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);
    } else {
        //GPR_ASSERT(status_ == FINISH);
        if (status_ != FINISH) {
            APIGWLogWARN(logSrv_, "gRPC server state machine has an error - undefined status");
        }
        delete this;
    }
}

void
gRPCServerImplCellConfigReport::setLogService(const log_service_t* logSrv) {
    this->logSrv = logSrv;
}
