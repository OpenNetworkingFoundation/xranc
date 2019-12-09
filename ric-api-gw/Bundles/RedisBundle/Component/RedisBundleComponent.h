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

#ifndef _REDIS_BUNDLE_COMPONENT_H_
#define _REDIS_BUNDLE_COMPONENT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#include <log_service.h>
#include <log_helper.h>
#include <hiredis.h>

#include <gRPCAPIs/cpp/gRPCServers/gRPCServer-CellConfigReport.h>

#include "../Activator/RedisBundleActivator.h"
#include "../../../APIs/Bundles/AbstractBundleComponent.h"
#include "../../../APIs/GWCore/AbstractGWCoreComponent.h"
#include "../../../APIs/Common/APIGwLogServiceWrapper.h"

#define REDIS_DB_IP "172.17.0.2"
#define REDIS_DB_PORT 6379
#define REDIS_TIMEOUT_SEC 1
#define REDIS_TIMOUET_USEC 500000

class RedisBundleComponent : public AbstractBundleComponent {

    public:
        RedisBundleComponent() = default;
        ~RedisBundleComponent() = default;

        void setLogService(const log_service_t* logSrv);
        void notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> statements);
        void registerBundle();
        void unregisterBundle();

        void init();
        void start();
        void stop();
        void deinit();

        void setGWCoreComponent(AbstractGWCoreComponent* gwcore);
        AbstractGWCoreComponent* getGWCoreComponent();

        // for Redis access
        void updateCellConfigReport(std::map<std::string, std::map<std::string, std::string>> statements);

    protected:

    private:
        const log_service_t* logSrv {nullptr};
        AbstractGWCoreComponent* gwCoreComponent {nullptr};
};

#endif /* _REDIS_BUNDLE_COMPONENT_H_ */