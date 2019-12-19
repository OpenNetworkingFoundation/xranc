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

#ifndef _GRPCSERVER_UEADMISSIONSTATUS_H_
#define _GRPCSERVER_UEADMISSIONSTATUS_H_

#include "gRPCServer.h"
#include "../gRPCParams/gRPCParam-UEAdmissionStatusMsg.h"
#include "../gRPCPB/gRPC-UEAdmissionStatus.grpc.pb.h"

class gRPCServerUEAdmissionStatus : public gRPCServer {

    public:
        gRPCServerUEAdmissionStatus();
        ~gRPCServerUEAdmissionStatus();

        virtual void run() = 0;
        virtual void handleRPCs() = 0;
        virtual void shutdownGRPCServer() = 0;

    private:

    protected:
        class AbstractCallData {
            public:
                AbstractCallData(gRPCUEAdmissionStatus::gRPCUEAdmissionStatusUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq);
                virtual void proceed() = 0;

            protected:
                gRPCUEAdmissionStatus::gRPCUEAdmissionStatusUpdater::AsyncService* service_;
                grpc::ServerCompletionQueue* cq_;
                grpc::ServerContext ctx_;
                gRPCUEAdmissionStatus::gMSGUEAdmissionStatusValues request_;
                gRPCUEAdmissionStatus::gMsgResults reply_ ;
                grpc::ServerAsyncResponseWriter<gRPCUEAdmissionStatus::gMsgResults> responder_;
                gRPCServerUEAdmissionStatus* grpcServerUEAdmissionStatus_;
        };

        std::unique_ptr<grpc::ServerCompletionQueue> cq;
        gRPCUEAdmissionStatus::gRPCUEAdmissionStatusUpdater::AsyncService service;
        std::unique_ptr<grpc::Server> server;
};

#endif /* _GRPCSERVER_UEADMISSIONSTATUS_H_ */