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

#ifndef _GRPCCLIENTIMPL_UEADMISSIONSTATUS_H_
#define _GRPCCLIENTIMPL_UEADMISSIONSTATUS_H_

#include <gRPCAPIs/cpp/gRPCClients/gRPCClient-UEAdmissionStatus.h>
#include <gRPCAPIs/cpp/gRPCPB/gRPC-UEAdmissionStatus.grpc.pb.h>
#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-UEAdmissionStatusMsg.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using gRPCUEAdmissionStatus::gRPCUEAdmissionStatusUpdater;
using gRPCUEAdmissionStatus::gMSGUEAdmissionStatusValues;

class gRPCClientImplUEAdmissionStatus : public gRPCClientUEAdmissionStatus {

    public:
        explicit gRPCClientImplUEAdmissionStatus(std::shared_ptr<Channel> channel)
            : stub_(gRPCUEAdmissionStatusUpdater::NewStub(channel)) {};

        int UpdateUEAdmissionStatus(gRPCParamUEAdmissionStatusMsg ueAdmissionStatusMsg);

    private:

    protected:
        std::unique_ptr<gRPCUEAdmissionStatusUpdater::Stub> stub_;
};

#endif /* _GRPCCLIENTIMPL_UEADMISSIONSTATUS_H_ */