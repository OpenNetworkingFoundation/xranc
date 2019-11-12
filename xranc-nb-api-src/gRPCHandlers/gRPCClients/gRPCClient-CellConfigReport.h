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

#ifndef _GRPCCLIENT_CELLCONFIGREPORT_H_
#define _GRPCCLIENT_CELLCONFIGREPORT_H_

#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "../../protobufs/gRPC-CellConfigReport.grpc.pb.h"
#include "../gRPCParams/gRPCParam-CellConfigReportMsg.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using gRPCCellConfigReport::gRPCCellConfigReportUpdater;
using gRPCCellConfigReport::gMsgECGI;
using gRPCCellConfigReport::gMsgCandScell;
using gRPCCellConfigReport::gMsgCellConfigValues;
using gRPCCellConfigReport::gMsgResults;

class gRPCClientCellConfigReport {
    public:
        explicit gRPCClientCellConfigReport(std::shared_ptr<Channel> channel)
            : stub_(gRPCCellConfigReportUpdater::NewStub(channel)) {};
        int UpdateCellConfig(gRPCParamCellConfigReportMsg cellConfigReport);

    private:
        std::unique_ptr<gRPCCellConfigReportUpdater::Stub> stub_;
};

#endif /* _GRPCCLIENT_CELLCONFIGREPORT_H_ */
