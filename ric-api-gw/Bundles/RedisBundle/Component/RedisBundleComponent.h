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

#include "../Activator/RedisBundleActivator.h"
#include "../../../APIs/Bundles/AbstractBundleComponent.h"
#include "../../../APIs/GWCore/AbstractGWCoreComponent.h"
#include "../../../APIs/Common/APIGwLogServiceWrapper.h"

#define REDIS_DB_IP "172.17.0.2"
#define REDIS_DB_PORT 6379
#define REDIS_TIMEOUT_SEC 1
#define REDIS_TIMOUET_USEC 500000

// To decode message
// To-Do: Need to make an encoder/decoder for this
#define DB_ECGI_KEY "ECGI" // Hash in eNB
#define DB_ENB_KEY "ENB" // Hash ECGI - ECGI ID, CAND-SCELLS - CAND-SCELLS ID
#define DB_CAND_SCELLS_KEY "CAND-SCELLS" // List in eNB

#define DB_ECGI_LIST "SET:ECGI"
#define DB_ENB_LIST "SET:ENB"
#define DB_CSCELLS_LIST "SET:CAND-SCELLS"

#define DB_PLMNID_KEY "PLMN-ID" // Value in ECGI
#define DB_ECID_KEY "ECID" // Value in ECGI

#define DB_CAND_SCELL_KEY "CAND-SCELL" // Values in CAND-SCELLS
#define DB_PCI_KEY "PCI" // values in CAND-SCELL and eNB
#define DB_EARFCN_DL "EARFCN-DL" // values in eNB
#define DB_EARFCN_UL "EARFCN-UL" // values in eNB
#define DB_RBS_PER_TTI_DL "RBS-PER-TTI-DL" // values in eNB
#define DB_RBS_PER_TTI_UL "RBS-PER-TTI-UL" // values in eNB
#define DB_NUM_TX_ANTENNAS "NUM_TX_ANTENNAS" // values in eNB
#define DB_DUPLEX_MODE "DUPLEX-MODE" // values in eNB
#define DB_MAX_NUM_CONNECTED_UES "MAX-NUM-CONNECTED-UES" // values in eNB
#define DB_MAX_NUM_CONNECTED_BEARERS "MAX-NUM-CONNECTED-BEARERS" // values in eNB
#define DB_MAX_NUM_UES_SCHED_PER_TTI_DL "MAX-NUM-UES-SCHED-PER-TTI-DL" // values in eNB
#define DB_MAX_NUM_UES_SCHED_PER_TTI_UL "MAX-NUM-UES-SCHED-PER-TTI-UL" // values in eNB
#define DB_DFLS_SCHED_ENABLE "DFLS-SCHED-ENABLE" // values in eNB

#define DB_KEY_PREFIX_ECGI "ECGI"
#define DB_KEY_PREFIX_ENB "eNB" // + ECGI
#define DB_KEY_PREFIX_CAND_SCELL "CAND-SCELL" // + ECGI

class RedisBundleComponent : public AbstractBundleComponent {

    public:
        RedisBundleComponent() = default;
        ~RedisBundleComponent() = default;

        void setLogService(const log_service_t* logSrv);
        void notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> message);
        void registerBundle();
        void unregisterBundle();

        void init();
        void start();
        void stop();
        void deinit();

        void setGWCoreComponent(AbstractGWCoreComponent* gwcore);
        AbstractGWCoreComponent* getGWCoreComponent();

        // for Redis access
        void updateCellConfigReport(std::map<std::string, std::map<std::string, std::string>> message);

    protected:

    private:
        const log_service_t* logSrv {nullptr};
        AbstractGWCoreComponent* gwCoreComponent {nullptr};
};

#endif /* _REDIS_BUNDLE_COMPONENT_H_ */