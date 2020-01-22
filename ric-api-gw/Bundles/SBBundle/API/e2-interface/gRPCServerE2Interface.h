/*
 * Copyright 2020-present Open Networking Foundation
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

#ifndef _GRPCSERVERE2INTERFACE_H_
#define _GRPCSERVERE2INTERFACE_H_

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <log_service.h>
#include <log_helper.h>
#include "e2-interface.grpc.pb.h"

#include "../../../../APIs/Common/APIGwLogServiceWrapper.h"
#include "../../Component/SBBundleComponent.h"
#include "../../../../APIs/GWCore/AbstractGWCoreComponent.h"
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

#define DB_UE_KEY "UE"
#define DB_UE_LIST_CRNTI "SET:UES-CRNTI"
#define DB_UE_LIST_IMSI "SET:UES-IMSI"

#define DB_CRNTI_KEY "CRNTI" // C-RNTI value
#define DB_UE_INFO_KEY "UE-INFO"

#define DB_MME_UE_S1AP_ID_KEY "MME-UE-S1AP-ID"
#define DB_ENB_UE_S1AP_ID_KEY "ENB-UE-S1AP-ID"
#define DB_IMSI_KEY "IMSI"


class gRPCServerE2Interface final {

    public:
        gRPCServerE2Interface();
        gRPCServerE2Interface(AbstractGWCoreComponent* gwCoreComponent);
        gRPCServerE2Interface(const log_service_t* logSrv, AbstractGWCoreComponent* gwCoreComponent);
        ~gRPCServerE2Interface();

        void run();
        void handleRPCs();
        void shutdownGRPCServer();

        void setLogService(const log_service_t* logSrv);
        void setGWCoreComponent(AbstractGWCoreComponent* gwCoreComponent);
        AbstractGWCoreComponent* getGWCoreComponent();

        std::string getServerIP();
        void setServerIP(std::string serverIP);
        std::string getServerPort();
        void setServerPort(std::string serverPort);

    private:
        class CallData {
            public:
                CallData(interface::e2::E2InterfaceService::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent, const log_service_t* logSrv);
                CallData(interface::e2::E2InterfaceService::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent);
                void proceed();

            private:
                interface::e2::E2InterfaceService::AsyncService* service_;
                grpc::ServerCompletionQueue* cq_;
                grpc::ServerContext ctx_;
                interface::e2::E2Message request_;
                interface::e2::ServiceResult reply_;
                grpc::ServerAsyncResponseWriter<interface::e2::ServiceResult> responder_;
                gRPCServerE2Interface* grpcServerE2Interface_;
                typedef enum { CREATE, PROCESS, FINISH } CallStatus;
                CallStatus status_;
                AbstractGWCoreComponent* gwCoreComponent_ {nullptr};
                const log_service_t* logSrv_ {nullptr};

                // private functions to handle the state machine
                int dispatch(interface::e2::E2Message message);
                void updateCellConfigReport(interface::e2::E2MessagePayload payload);
                void updateUEAdmissionStatus(interface::e2::E2MessagePayload payload);
                void updateUEContextUpdate(interface::e2::E2MessagePayload payload);
        };
        std::string serverIP;
        std::string serverPort;
        std::unique_ptr<grpc::ServerCompletionQueue> cq;
        interface::e2::E2InterfaceService::AsyncService service;
        std::unique_ptr<grpc::Server> server;
        const log_service_t* logSrv {nullptr};
        AbstractGWCoreComponent* gwCoreComponent {nullptr};

    protected:

};

#endif /* _GRPCSERVERE2INTERFACE_H_ */