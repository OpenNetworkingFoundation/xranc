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

#ifndef _GRPCCLIENTE2INTERFACE_H_
#define _GRPCCLIENTE2INTERFACE_H_

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "e2-interface.grpc.pb.h"

class gRPCClientE2Interface {
    
    public:
        explicit gRPCClientE2Interface(std::shared_ptr<grpc::Channel> channel)
            : stub_(interface::e2::E2InterfaceService::NewStub(channel)) {};

        int UpdateAttribute(interface::e2::E2Message e2Message); // return result code
    private:
        std::unique_ptr<interface::e2::E2InterfaceService::Stub> stub_;

    protected:

};

#endif /* _GRPCCLIENTE2INTERFACE_H_ */