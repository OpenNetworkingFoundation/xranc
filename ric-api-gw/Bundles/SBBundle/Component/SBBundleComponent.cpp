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
SBBundleComponent::setGWCoreComponent(AbstractGWCoreComponent* gwcore) {
    std::cout << "SBBundleComponent - setGWCoreComponent" << std::endl;
    this->gwCoreComponent = gwcore;
}

void 
SBBundleComponent::setLogService(const log_service_t* logSrv) {
    //for logging
    std::cout << "SBBundleComponent - setLogService" << std::endl;
    this->logSrv = logSrv;
}

void
SBBundleComponent::notifyEvent() {
    std::cout << "SBBundleComponent - notifyEvent" << std::endl;
    APIGWLogINFO(this->logSrv, "SBBundleComponent - notifyEvent");
}

void
SBBundleComponent::registerBundle() {
    std::cout << "SBBundleComponent - registerBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Register " << SB_BUNDLE_KEY << " Bundle";
    if (this->logSrv != nullptr) {
        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    }
    if (gwCoreComponent) {
        gwCoreComponent->registerBundle(SB_BUNDLE_KEY, this);
        logMsg.flush();
        logMsg << "Finished to register " << SB_BUNDLE_KEY << " Bundle";
        if (this->logSrv != nullptr) {
            APIGWLogINFO(this->logSrv, logMsg.str().c_str());
        }
    } else {
        if (this->logSrv != nullptr) {
            APIGWLogERROR(this->logSrv, logMsg.str().c_str());
        }
    }
}

void
SBBundleComponent::unregisterBundle() {
    std::cout << "SBBundleComponent - unregisterBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Unregister " << SB_BUNDLE_KEY << " Bundle";
    if (this->logSrv != nullptr) {
        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    }
    if (gwCoreComponent) {
        gwCoreComponent->unregisterBundle(SB_BUNDLE_KEY);
        logMsg.flush();
        logMsg << "Finished to register " << SB_BUNDLE_KEY << " Bundle";
        if (this->logSrv != nullptr) {
            APIGWLogINFO(this->logSrv, logMsg.str().c_str());
        }
    } else {
        if (this->logSrv != nullptr) {
            APIGWLogERROR(this->logSrv, logMsg.str().c_str());
        }
    }
}

void
SBBundleComponent::runGRPCServer() {
    
    //To-Do: remove this hard coded part and get this information from GWCore
    service = new gRPCServerImplCellConfigReport();
    service->setServerIP(GRPC_SB_IP);
    service->setServerPort(GRPC_SB_PORT);
    ((gRPCServerImplCellConfigReport*) service)->setLogService(logSrv);
    th1 = std::thread ([this] {service->run();});
    //service->run();
}

void
SBBundleComponent::killGRPCServer() {
    service->shutdownGRPCServer();
    th1.detach();
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
