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

using namespace celix::dm;

DmActivator*
DmActivator::create(DependencyManager& mng) {
    return new GWCoreActivator(mng);
}

void
GWCoreActivator::init() {

    auto component = std::unique_ptr<GWCoreComponent>(new GWCoreComponent());

    Properties props {};
    props["name"] = GWCORE_NAME;
    
    Properties cmdProps = setCmdGwCoreInfoProp(GWCORE_CMD_INFO_NAME, GWCORE_CMD_INFO_NAME, "Print information about the GWCoreComponent");
    component = setCmdGwCoreInfoFunc(std::move(component));

    Component<GWCoreComponent>& tmpComponent = mng.createComponent(std::move(component))
        .addInterface<AbstractGWCoreComponent>(GWCORE_VERSION, props)
        .addCInterface(&cmdGwCoreInfo, OSGI_SHELL_COMMAND_SERVICE_NAME, "", cmdProps)
        .setCallbacks(&GWCoreComponent::init, &GWCoreComponent::start, &GWCoreComponent::stop, &GWCoreComponent::deinit);

    tmpComponent.createCServiceDependency<log_service_t>(OSGI_LOGSERVICE_NAME)
        .setRequired(true)
        .setCallbacks(&GWCoreComponent::setLogService);
}

void
GWCoreActivator::deinit() {

}


Properties
GWCoreActivator::setCmdGwCoreInfoProp(std::string name, std::string usage, std::string desc) {
    Properties cmdProps;
    cmdProps[OSGI_SHELL_COMMAND_NAME] = name;
    cmdProps[OSGI_SHELL_COMMAND_USAGE] = usage;
    cmdProps[OSGI_SHELL_COMMAND_DESCRIPTION] = desc;
    return cmdProps;
}

std::unique_ptr<GWCoreComponent>
GWCoreActivator::setCmdGwCoreInfoFunc(std::unique_ptr<GWCoreComponent> component) {
    cmdGwCoreInfo.handle = component.get();
    cmdGwCoreInfo.executeCommand = [](void *handle, char* line, FILE* out, FILE *err) {
        GWCoreComponent* component = (GWCoreComponent*)handle;
        return component->infoCmd(line, out, err);
    };
    return std::move(component);
}