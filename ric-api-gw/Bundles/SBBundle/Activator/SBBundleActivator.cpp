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

using namespace celix::dm;

DmActivator*
DmActivator::create(DependencyManager& mng) {
    return new SBBundleActivator(mng);
}

void
SBBundleActivator::init() {

    auto component = std::unique_ptr<SBBundleComponent>(new SBBundleComponent());

    Properties props {};
    props["name"] = SB_BUNDLE_KEY;

    Component<SBBundleComponent>& tmpComponent = mng.createComponent(std::move(component))
        .addInterface<SBBundleComponent>(SB_BUNDLE_VERSION, props)
        .setCallbacks(&SBBundleComponent::init, &SBBundleComponent::start, &SBBundleComponent::stop, &SBBundleComponent::deinit);
        
    tmpComponent.createServiceDependency<AbstractGWCoreComponent>()
        .setRequired(true)
        .setFilter("(name=GWCore)")
        .setCallbacks(&SBBundleComponent::setGWCoreComponent);

    tmpComponent.createCServiceDependency<log_service_t>(OSGI_LOGSERVICE_NAME)
        .setRequired(true)
        .setCallbacks(&SBBundleComponent::setLogService);

}

void
SBBundleActivator::deinit() {
    
}