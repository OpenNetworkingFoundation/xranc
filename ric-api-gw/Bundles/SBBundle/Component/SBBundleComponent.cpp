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

int
SBBundleComponent::infoCmd(char* line, FILE *out, FILE* err) {
    fprintf(out, "SBBundle is running");
    std::cout << std::endl;
    std::cout << "SBBundle is running: " << line << std::endl;
    return 0;
}

void
SBBundleComponent::notifyEvent() {
    std::cout << "SBBundleComponent - notifyEvent" << std::endl;
}

void
SBBundleComponent::registerBundle() {
    std::cout << "register bundle: " << SB_BUNDLE_KEY << std::endl;
    if (gwCoreComponent) {
        gwCoreComponent->registerBundle(SB_BUNDLE_KEY, this);
    } else {
        std::cout << "GWCore is not ready; cannot register this bundle on GWCore" << std::endl;
    }
}

void
SBBundleComponent::unregisterBundle() {
    std::cout << "unregister bundle: " << SB_BUNDLE_KEY << std::endl;
    if (gwCoreComponent) {
        gwCoreComponent->unregisterBundle(SB_BUNDLE_KEY);
    } else {
        std::cout << "GWCore is not ready; nothing to unregister" << std::endl;
    }
}

void
SBBundleComponent::init() {
    std::cout << "SBBundleComponent - init" << std::endl;
}

void
SBBundleComponent::start() {
    this->registerBundle();
    std::cout << "SBBundleComponent - start" << std::endl;
}

void
SBBundleComponent::stop() {
    this->unregisterBundle();
    std::cout << "SBBundleComponent - stop" << std::endl;
}

void
SBBundleComponent::deinit() {
    std::cout << "SBBundleComponent - deinit" << std::endl;
}
