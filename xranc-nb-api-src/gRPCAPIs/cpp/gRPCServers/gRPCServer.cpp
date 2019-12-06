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

#include "gRPCServer.h"

gRPCServer::gRPCServer() {}

gRPCServer::~gRPCServer() {}

std::string 
gRPCServer::getServerIP() {
    return serverIP;
}

void 
gRPCServer::setServerIP(std::string serverIP) {
    this->serverIP = serverIP;
}

std::string 
gRPCServer::getServerPort() {
    return serverPort;
}

void 
gRPCServer::setServerPort(std::string serverPort) {
    this->serverPort = serverPort;
}