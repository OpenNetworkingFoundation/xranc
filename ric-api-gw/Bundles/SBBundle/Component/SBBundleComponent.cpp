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

#include "SBBundleComponent.h"

void 
SBBundleComponent::setLogService(const log_service_t* logSrv) {
    //for logging
    std::cout << "SBBundleComponent - setLogService" << std::endl;
    this->logSrv = logSrv;
}

void
SBBundleComponent::notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> message) {
    APIGWLogINFO(this->logSrv, "SBBundleComponent - notifyEvent");
}

void
SBBundleComponent::registerBundle() {
    std::cout << "SBBundleComponent - registerBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Register " << SB_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    
    if (gwCoreComponent) {
        gwCoreComponent->registerBundle(SB_BUNDLE_KEY, this);
        logMsg.flush();
        logMsg << "Finished to register " << SB_BUNDLE_KEY << " Bundle";

        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
SBBundleComponent::unregisterBundle() {
    std::cout << "SBBundleComponent - unregisterBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Unregister " << SB_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());

    if (gwCoreComponent) {
        gwCoreComponent->unregisterBundle(SB_BUNDLE_KEY);
        logMsg.flush();
        logMsg << "Finished to register " << SB_BUNDLE_KEY << " Bundle";
        
        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
SBBundleComponent::runGRPCServer() {

    serviceE2Interface = new gRPCServerE2Interface(logSrv, getGWCoreComponent());
    serviceE2Interface->setServerIP(GRPC_SB_IP);
    serviceE2Interface->setServerPort(GRPC_SB_PORT);
    th_e2interface = new std::thread ([this] {serviceE2Interface->run();});
}

void
SBBundleComponent::killGRPCServer() {
    serviceE2Interface->shutdownGRPCServer();
    th_e2interface->join();
    delete th_e2interface;
}

void
SBBundleComponent::init() {
    std::cout << "SBBundleComponent - init" << std::endl;
}

void
SBBundleComponent::start() {
    std::cout << "SBBundleComponent - start" << std::endl;
    this->registerBundle();
    runGRPCServer();
}

void
SBBundleComponent::stop() {
    std::cout << "SBBundleComponent - stop" << std::endl;
    killGRPCServer();
    this->unregisterBundle();
}

void
SBBundleComponent::deinit() {
    std::cout << "SBBundleComponent - deinit" << std::endl;
}

void
SBBundleComponent::setGWCoreComponent(AbstractGWCoreComponent* gwcore) {
    this->gwCoreComponent = gwcore;
}

AbstractGWCoreComponent*
SBBundleComponent::getGWCoreComponent() {
    return gwCoreComponent;
}
