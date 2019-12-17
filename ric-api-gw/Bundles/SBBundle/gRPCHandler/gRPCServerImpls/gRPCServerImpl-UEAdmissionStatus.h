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

#ifndef _GRPCSERVERIMPL_UEADMISSIONSTATUS_H_
#define _GRPCSERVERIMPL_UEADMISSIONSTATUS_H_

#include <iostream>
#include <sstream>
#include <exception>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <log_service.h>
#include <log_helper.h>

#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-UEAdmissionStatusMsg.h>
#include <gRPCAPIs/cpp/gRPCServers/gRPCServer-UEAdmissionStatus.h>
#include <gRPCAPIs/cpp/gRPCPB/gRPC-UEAdmissionStatus.grpc.pb.h>

#include "Common/APIGwLogServiceWrapper.h"
#include "SBBundleComponent.h"
#include "GWCore/AbstractGWCoreComponent.h"
#include "../../../RedisBundle/Activator/RedisBundleActivator.h"
#include "../../../ONOSBundle/Activator/ONOSBundleActivator.h"

// To decode message
// To-Do: Need to make an encoder/decoder for this
#define DB_ECGI_KEY "ECGI"
#define DB_UE_KEY "UE"

#define DB_UE_LIST_IN_ENB "UES"
#define DB_UE_LIST_CRNTI "SET:UES-CRNTI"

#define DB_CRNTI_KEY "CRNTI" // C-RNTI value
#define DB_PLMNID_KEY "PLMN-ID" // Value in ECGI
#define DB_ECID_KEY "ECID" // Value in ECGI

class gRPCServerImplUEAdmissionStatus final : public gRPCServerUEAdmissionStatus {

    public:
        gRPCServerImplUEAdmissionStatus();
        gRPCServerImplUEAdmissionStatus(AbstractGWCoreComponent* gwCoreComponent);
        gRPCServerImplUEAdmissionStatus(const log_service_t* logSrv, AbstractGWCoreComponent* gwCoreComponent);
        ~gRPCServerImplUEAdmissionStatus();

        void run();
        void handleRPCs();
        void shutdownGRPCServer();

        void setLogService(const log_service_t* logSrv);
        void setGWCoreComponent(AbstractGWCoreComponent* gwCoreComponent);
        AbstractGWCoreComponent* getGWCoreComponent();


    private:
        class CallData : public AbstractCallData {
            public:
                CallData(gRPCUEAdmissionStatus::gRPCUEAdmissionStatusUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent, const log_service_t* logSrv);
                CallData(gRPCUEAdmissionStatus::gRPCUEAdmissionStatusUpdater::AsyncService* service, grpc::ServerCompletionQueue* cq, AbstractGWCoreComponent* gwCoreComponent);
                void proceed();

            private:
                enum CallStatus { CREATE, PROCESS_UPDATEADMSTAT, FINISH };
                CallStatus status_;
                AbstractGWCoreComponent* gwCoreComponent_ {nullptr};
                const log_service_t* logSrv_ {nullptr};
        };

        const log_service_t* logSrv {nullptr};
        AbstractGWCoreComponent* gwCoreComponent {nullptr};

    protected:
};

#endif /* _GRPCSERVERIMPL_UEADMISSIONSTATUS_H_ */