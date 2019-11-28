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
    std::cout << "GWCoreComponent - notifyEvent" << std::endl;
}

void
GWCoreComponent::registerBundle() {
    std::cout << "GWCoreComponent - registerBundle" << std::endl;
}

int
GWCoreComponent::infoCmd(char* line, FILE *out, FILE* err) {
    fprintf(out, "GWCore is running");
    return 0;
}