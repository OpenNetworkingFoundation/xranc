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

#ifndef _CELIX_ONOS_BUNDLE_COMPONENT_H_
#define _CELIX_ONOS_BUNDLE_COMPONENT_H_

#include <iostream>
#include <string>
#include <sstream>

#include <log_service.h>
#include <log_helper.h>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "../../../APIs/Bundles/AbstractBundleComponent.h"
#include "../../../APIs/GWCore/AbstractGWCoreComponent.h"
#include "../Activator/ONOSBundleActivator.h"
#include "../../../APIs/Common/APIGwLogServiceWrapper.h"

class ONOSBundleComponent : AbstractBundleComponent {

    public:
        ONOSBundleComponent() = default;
        ~ONOSBundleComponent() = default;

        void setLogService(const log_service_t* logSrv);
        void notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> message);
        void registerBundle();
        void unregisterBundle();

        void init();
        void start();
        void stop();
        void deinit();

        // for gRPC to send CellConfigReport
        int updateCellConfig(std::map<std::string, std::map<std::string, std::string>> message);

        void setGWCoreComponent(AbstractGWCoreComponent* gwcore);
        AbstractGWCoreComponent* getGWCoreComponent();

    protected:

    private:
        AbstractGWCoreComponent* gwCoreComponent {nullptr};
        const log_service_t* logSrv {nullptr};
};

#endif /* _CELIX_ONOS_BUNDLE_COMPONENT_H_ */