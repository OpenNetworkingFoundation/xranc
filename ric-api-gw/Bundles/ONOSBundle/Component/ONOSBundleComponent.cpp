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

#include "ONOSBundleComponent.h"

void 
ONOSBundleComponent::setLogService(const log_service_t* logSrv) {
    //for logging
    std::cout << "ONOSBundleComponent - setLogService" << std::endl;
    this->logSrv = logSrv;
}

void
ONOSBundleComponent::notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> message) {
    std::string notifyResult = "SRC: " + srcBundle + " DST: " + dstBundle;
    APIGWLogDEBUG(logSrv, notifyResult);
    updateCellConfig(message);
}

void
ONOSBundleComponent::registerBundle() {
    std::cout << "ONOSBundleComponent - registerBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Register " << ONOS_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    
    if (gwCoreComponent) {
        gwCoreComponent->registerBundle(ONOS_BUNDLE_KEY, this);
        logMsg.flush();
        logMsg << "Finished to register " << ONOS_BUNDLE_KEY << " Bundle";

        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
ONOSBundleComponent::unregisterBundle() {
    std::cout << "ONOSBundleComponent - unregisterBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Unregister " << ONOS_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());

    if (gwCoreComponent) {
        gwCoreComponent->unregisterBundle(ONOS_BUNDLE_KEY);
        logMsg.flush();
        logMsg << "Finished to register " << ONOS_BUNDLE_KEY << " Bundle";
        
        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

int
ONOSBundleComponent::updateCellConfig(std::map<std::string, std::map<std::string, std::string>> statements) {
    return 0;
}

void
ONOSBundleComponent::init() {
    std::cout << "ONOSBundleComponent - init" << std::endl;
}

void
ONOSBundleComponent::start() {
    std::cout << "ONOSBundleComponent - start" << std::endl;
    this->registerBundle();
}

void
ONOSBundleComponent::stop() {
    std::cout << "ONOSBundleComponent - stop" << std::endl;
    this->unregisterBundle();
}

void
ONOSBundleComponent::deinit() {
    std::cout << "ONOSBundleComponent - deinit" << std::endl;
}
void
ONOSBundleComponent::setGWCoreComponent(AbstractGWCoreComponent* gwcore) {
    this->gwCoreComponent = gwcore;
}

AbstractGWCoreComponent*
ONOSBundleComponent::getGWCoreComponent() {
    return gwCoreComponent;
}
