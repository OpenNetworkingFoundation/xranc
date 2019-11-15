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

#ifndef _GRPCCLIENT_H_
#define _GRPCCLIENT_H_

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

class gRPCClient {
    
    public:
        gRPCClient();
        ~gRPCClient();

    private:

    protected:

};

#endif /* _GRPCCLIENT_H_ */