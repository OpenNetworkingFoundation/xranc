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

#ifndef _CELIX_GWCORE_ACTIVATOR_H_
#define _CELIX_GWCORE_ACTIVATOR_H_

#include <iostream>
#include <string>

#include <celix/dm/DmActivator.h>
#include <command.h>

#include "../Component/GWCoreComponent.h"

class GWCoreActivator : public DmActivator {

    public:
        GWCoreActivator(DependencyManager& mng) : DmActivator(mng) {}
        virtual void init();
        virtual void deinit();
        
        //for CLI
        Properties setCmdGwCoreInfoProp(std::string name, std::string usage, std::string desc);
        std::unique_ptr<GWCoreComponent> setCmdGwCoreInfoFunc(std::unique_ptr<GWCoreComponent> component);

    protected:

    private:
        command_service_t cmdGwCoreInfo {nullptr, nullptr};
};

#endif /* _CELIX_GWCORE_ACTIVATOR_H_ */