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

#include "GWCoreActivator.h"
#include "../Component/GWCoreComponent.h"

using namespace celix::dm;

DmActivator*
DmActivator::create(DependencyManager& mng) {
    return new GWCoreActivator(mng);
}

void
GWCoreActivator::init() {
    auto component = std::unique_ptr<GWCoreComponent>(new GWCoreComponent());

    Properties cmdProps;
    cmdProps[OSGI_SHELL_COMMAND_NAME] = "gwcoreinfo";
    cmdProps[OSGI_SHELL_COMMAND_USAGE] = "gwcoreinfo";
    cmdProps[OSGI_SHELL_COMMAND_DESCRIPTION] = "Print information about the GWCoreComponent";

    cmd.handle = component.get();
    cmd.executeCommand = [](void *handle, char* line, FILE* out, FILE *err) {
        GWCoreComponent* component = (GWCoreComponent*)handle;
        return component->infoCmd(line, out, err);
    };

    mng.createComponent(std::move(component))
        .addInterface<AbstractGWCoreComponent>(GWCORE_VERSION)
        .addCInterface(&cmd, OSGI_SHELL_COMMAND_SERVICE_NAME, "", cmdProps)
        .setCallbacks(&GWCoreComponent::init, &GWCoreComponent::start, &GWCoreComponent::stop, &GWCoreComponent::deinit);

}

void
GWCoreActivator::deinit() {

}