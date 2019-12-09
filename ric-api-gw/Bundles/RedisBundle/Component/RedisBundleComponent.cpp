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

#include "RedisBundleComponent.h"

void 
RedisBundleComponent::setGWCoreComponent(AbstractGWCoreComponent* gwcore) {
    std::cout << "RedisBundleComponent - setGWCoreComponent" << std::endl;
    this->gwCoreComponent = gwcore;
}

void 
RedisBundleComponent::setLogService(const log_service_t* logSrv) {
    //for logging
    std::cout << "RedisBundleComponent - setLogService" << std::endl;
    this->logSrv = logSrv;
}

void
RedisBundleComponent::notifyEvent() {
    std::cout << "RedisBundleComponent - notifyEvent" << std::endl;
    APIGWLogINFO(this->logSrv, "RedisBundleComponent - notifyEvent");
}

void
RedisBundleComponent::registerBundle() {
    std::cout << "RedisBundleComponent - registerBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Register " << REDIS_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    
    if (gwCoreComponent) {
        gwCoreComponent->registerBundle(REDIS_BUNDLE_KEY, this);
        logMsg.flush();
        logMsg << "Finished to register " << REDIS_BUNDLE_KEY << " Bundle";

        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
RedisBundleComponent::unregisterBundle() {
    std::cout << "RedisBundleComponent - unregisterBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Unregister " << REDIS_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());

    if (gwCoreComponent) {
        gwCoreComponent->unregisterBundle(REDIS_BUNDLE_KEY);
        logMsg.flush();
        logMsg << "Finished to register " << REDIS_BUNDLE_KEY << " Bundle";
        
        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
RedisBundleComponent::init() {
    std::cout << "RedisBundleComponent - init" << std::endl;
}

void
RedisBundleComponent::start() {
    std::cout << "RedisBundleComponent - start" << std::endl;
    this->registerBundle();
}

void
RedisBundleComponent::stop() {
    std::cout << "RedisBundleComponent - stop" << std::endl;
    this->unregisterBundle();
}

void
RedisBundleComponent::deinit() {
    std::cout << "RedisBundleComponent - deinit" << std::endl;
}
