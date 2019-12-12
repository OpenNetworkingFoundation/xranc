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

#include "ONOSBundleActivator.h"

using namespace celix::dm;

DmActivator*
DmActivator::create(DependencyManager& mng) {
    return new ONOSBundleActivator(mng);
}

void
ONOSBundleActivator::init() {

    auto component = std::unique_ptr<ONOSBundleComponent>(new ONOSBundleComponent());

    Properties props {};
    props["name"] = ONOS_BUNDLE_KEY;

    Component<ONOSBundleComponent>& tmpComponent = mng.createComponent(std::move(component))
        .addInterface<ONOSBundleComponent>(ONOS_BUNDLE_KEY, props)
        .setCallbacks(&ONOSBundleComponent::init, &ONOSBundleComponent::start, &ONOSBundleComponent::stop, &ONOSBundleComponent::deinit);
        
    std::stringstream gwCoreFilter;
    gwCoreFilter << "(name=" << GWCORE_NAME << ")";
    
    tmpComponent.createServiceDependency<AbstractGWCoreComponent>()
        .setRequired(true)
        .setFilter(gwCoreFilter.str())
        .setCallbacks(&ONOSBundleComponent::setGWCoreComponent);

    tmpComponent.createCServiceDependency<log_service_t>(OSGI_LOGSERVICE_NAME)
        .setRequired(true)
        .setCallbacks(&ONOSBundleComponent::setLogService);

}

void
ONOSBundleActivator::deinit() {
    
}