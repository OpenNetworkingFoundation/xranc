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

#include "SBBundleActivator.h"
#include "../Component/SBBundleComponent.h"

using namespace celix::dm;

DmActivator*
DmActivator::create(DependencyManager& mng) {
    return new SBBundleActivator(mng);
}

void
SBBundleActivator::init() {

    auto component = std::unique_ptr<SBBundleComponent>(new SBBundleComponent());
    
    Properties cmdProps;
    cmdProps[OSGI_SHELL_COMMAND_NAME] = "sbbundleinfo";
    cmdProps[OSGI_SHELL_COMMAND_USAGE] = "sbbundleinfo";
    cmdProps[OSGI_SHELL_COMMAND_DESCRIPTION] = "Print information about the SBBundleComponent";

    Properties props {};
    props["name"] = SB_BUNDLE_KEY;
        
    cmd.handle = component.get();
    cmd.executeCommand = [](void *handle, char* line, FILE* out, FILE *err) {
        SBBundleComponent* component = (SBBundleComponent*)handle;
        return component->infoCmd(line, out, err);
    };

    Component<SBBundleComponent>& tmpComponent = mng.createComponent(std::move(component))
        .addInterface<SBBundleComponent>(SB_BUNDLE_VERSION, props)
        .setCallbacks(&SBBundleComponent::init, &SBBundleComponent::start, &SBBundleComponent::stop, &SBBundleComponent::deinit)
        .addCInterface(&cmd, OSGI_SHELL_COMMAND_SERVICE_NAME, "", cmdProps);

        
    tmpComponent.createServiceDependency<AbstractGWCoreComponent>()
        .setRequired(true)
        .setFilter("(name=GWCore)")
        .setCallbacks(&SBBundleComponent::setGWCoreComponent);

}

void
SBBundleActivator::deinit() {

}