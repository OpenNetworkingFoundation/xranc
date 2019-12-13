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

#ifndef _GRPCSERVER_CELLCONFIGREPORT_H_
#define _GRPCSERVER_CELLCONFIGREPORT_H_

#include "gRPCServer.h"
#include "../gRPCParams/gRPCParam-CellConfigReportMsg.h"
#include "../gRPCPB/gRPC-CellConfigReport.grpc.pb.h"

class gRPCServerCellConfigReport : public gRPCServer {

    public:
        gRPCServerCellConfigReport();
        ~gRPCServerCellConfigReport();

        virtual void run() = 0;
        virtual void handleRPCs() = 0;

        virtual void shutdownGRPCServer() = 0;
        
    private:

    protected:
        class AbstractCallData {
            public:
                AbstractCallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq);
                virtual void proceed() = 0;

            protected:
                gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service_;
                grpc::ServerCompletionQueue* cq_;
                grpc::ServerContext ctx_;
                gRPCCellConfigReport::gMsgCellConfigValues request_;
                gRPCCellConfigReport::gMsgResults reply_;
                grpc::ServerAsyncResponseWriter<gRPCCellConfigReport::gMsgResults> responder_;
                gRPCServerCellConfigReport* grpcServerCellConfigReport_;
        };

        std::unique_ptr<grpc::ServerCompletionQueue> cq;
        gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService service;
        std::unique_ptr<grpc::Server> server;
};

#endif /* _GRPCSERVER_CELLCONFIGREPORT_H_ */