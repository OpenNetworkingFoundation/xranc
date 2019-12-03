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

#ifndef _CELIX_SB_BUNDLE_COMPONENT_H_
#define _CELIX_SB_BUNDLE_COMPONENT_H_

#include <iostream>
#include <string>

#include "../../../APIs/Bundles/AbstractBundleComponent.h"
#include "../../../APIs/GWCore/AbstractGWCoreComponent.h"
#include "../Activator/SBBundleActivator.h"

class SBBundleComponent : public AbstractBundleComponent {

    public:
        SBBundleComponent() = default;
        ~SBBundleComponent() = default;

        void setGWCoreComponent(AbstractGWCoreComponent* gwcore);
        int infoCmd(char* line, FILE* out, FILE* err);  //implements cmd service
        void notifyEvent() override;
        void registerBundle();
        void unregisterBundle();

        void init();
        void start();
        void stop();
        void deinit();
        
    protected:

    private:
        AbstractGWCoreComponent* gwCoreComponent {nullptr};
};



#endif /* _CELIX_SB_BUNDLE_COMPONENT_H_ */