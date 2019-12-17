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

#ifndef _GRPCSERVERIMPL_CELLCONFIGREPORT_H_
#define _GRPCSERVERIMPL_CELLCONFIGREPORT_H_

#include <iostream>
#include <sstream>
#include <exception>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <log_service.h>
#include <log_helper.h>

#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-CellConfigReportMsg.h>
#include <gRPCAPIs/cpp/gRPCServers/gRPCServer-CellConfigReport.h>
#include <gRPCAPIs/cpp/gRPCPB/gRPC-CellConfigReport.grpc.pb.h>

#include "Common/APIGwLogServiceWrapper.h"
#include "SBBundleComponent.h"
#include "GWCore/AbstractGWCoreComponent.h"
#include "../../../RedisBundle/Activator/RedisBundleActivator.h"
#include "../../../ONOSBundle/Activator/ONOSBundleActivator.h"

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
#define DB_UE_LIST_IN_ENB "UES"

class gRPCServerImplCellConfigReport final : public gRPCServerCellConfigReport {
    
    public:
        gRPCServerImplCellConfigReport();
        gRPCServerImplCellConfigReport(AbstractGWCoreComponent* gwCoreComponent);
        gRPCServerImplCellConfigReport(const log_service_t* logSrv, AbstractGWCoreComponent* gwCoreComponent);
        ~gRPCServerImplCellConfigReport();

        void run();
        void handleRPCs();
        void shutdownGRPCServer();

        void setLogService(const log_service_t* logSrv);
        void setGWCoreComponent(AbstractGWCoreComponent* gwCoreComponent);
        AbstractGWCoreComponent* getGWCoreComponent();

    private:
        class CallData : public AbstractCallData {
            public:
                CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent, const log_service_t* logSrv);
                CallData(gRPCCellConfigReport::gRPCCellConfigReportUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent);
                void proceed();

            private:
                enum CallStatus { CREATE, PROCESS_UPDATECELLCONFIG, FINISH };
                CallStatus status_;
                AbstractGWCoreComponent* gwCoreComponent_ {nullptr};
                const log_service_t* logSrv_ {nullptr};
        };

        const log_service_t* logSrv {nullptr};
        AbstractGWCoreComponent* gwCoreComponent {nullptr};

    protected:

};

#endif /* _GRPCSERVERIMPL_CELLCONFIGREPORT_H_ */