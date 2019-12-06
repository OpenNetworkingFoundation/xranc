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

#ifndef _GRPCSERVERIMPL_CELLCONFIGREPORT_H_
#define _GRPCSERVERIMPL_CELLCONFIGREPORT_H_

#include <iostream>
#include <sstream>
#include <exception>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <log_service.h>
#include <log_helper.h>

#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-CellConfigReportMsg.h>
#include <gRPCAPIs/cpp/gRPCServers/gRPCServer-CellConfigReport.h>
#include <gRPCAPIs/cpp/gRPCPB/gRPC-CellConfigReport.grpc.pb.h>

#include "../../../APIs/Common/APIGwLogServiceWrapper.h"
#include "../../Component/SBBundleComponent.h"

class gRPCServerImplCellConfigReport final : public gRPCServerCellConfigReport {
    
    public:
        gRPCServerImplCellConfigReport();
        ~gRPCServerImplCellConfigReport();

        void run();
        void handleRPCs();
        void shutdownGRPCServer();

        void setLogService(const log_service_t* logSrv);

    private:
        class CallData : public AbstractCallData {
            public:
                CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, const log_service_t* logSrv);
                CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq);
                void proceed();
            private:
                enum CallStatus { CREATE, PROCESS_UPDATECELLCONFIG, FINISH };
                CallStatus status_;
                const log_service_t* logSrv_ {nullptr};
        };

        const log_service_t* logSrv {nullptr};

    protected:

};

#endif /* _GRPCSERVERIMPL_CELLCONFIGREPORT_H_ */