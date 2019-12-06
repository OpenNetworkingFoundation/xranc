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

#ifndef _GRPCSERVER_H_
#define _GRPCSERVER_H_

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

class gRPCServer {

    public:
        gRPCServer();
        ~gRPCServer();
        std::string getServerIP();
        void setServerIP(std::string serverIP);
        std::string getServerPort();
        void setServerPort(std::string serverPort);
        
        virtual void run() = 0;
        virtual void handleRPCs() = 0;
        

    private:

    protected:
        std::string serverIP;
        std::string serverPort;
    
};


#endif /* _GRPCSERVER_H_ */