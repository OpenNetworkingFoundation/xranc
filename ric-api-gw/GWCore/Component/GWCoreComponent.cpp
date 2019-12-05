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

#include "GWCoreComponent.h"

void
GWCoreComponent::init() {
    std::cout << "GWCoreComponent - init" << std::endl;
}

void
GWCoreComponent::start() {
    std::cout << "GWCoreComponent - start" << std::endl;
}

void
GWCoreComponent::stop() {
    std::cout << "GWCoreComponent - stop" << std::endl;
}

void
GWCoreComponent::deinit() {
    std::cout << "GWCoreComponent - deinit" << std::endl;
}

void
GWCoreComponent::notifyEvent() {
    this->logSrv->log(this->logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) "Notify Event");
}

void
GWCoreComponent::setLogService(const log_service_t* logSrv) {
    std::cout << "GWCoreComponent - setLogService" << std::endl;
    this->logSrv = logSrv;
}


void
GWCoreComponent::registerBundle(std::string key, AbstractBundleComponent* bundleComponent) {
    std::cout << "GWCoreComponent - registerBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Register " << key << " Bundle";
    if (this->logSrv != nullptr) {
        this->logSrv->log(this->logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) logMsg.str().c_str());
    }
    addBundle(key, bundleComponent);
    logMsg.flush();
    logMsg << "Finished to register " << key << " Bundle";
    if (this->logSrv != nullptr) {
        this->logSrv->log(this->logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) logMsg.str().c_str());
    }
}

void
GWCoreComponent::unregisterBundle(std::string key) {
    std::cout << "GWCoreComponent - unregisterBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Unregister " << key << " Bundle";
    if (this->logSrv != nullptr) {
        this->logSrv->log(this->logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) logMsg.str().c_str());
    }
    removeBundle(key);
    logMsg.flush();
    logMsg << "Finished to unregister " << key << " Bundle";
    if (this->logSrv != nullptr) {
        this->logSrv->log(this->logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) logMsg.str().c_str());
    }
}

int
GWCoreComponent::infoCmd(char* line, FILE* out, FILE* err) {
    fprintf(out, "GWCore is running\n");
    fprintf(out, "Registered bundle list (%d bundles)\n", (int)bundles.size() );
    for (std::map<std::string, AbstractBundleComponent*>::iterator it = bundles.begin(); it != bundles.end(); it = ++it) {
        fprintf(out, "** %s bundle\n", it->first.c_str());
    }
    return 0;
}