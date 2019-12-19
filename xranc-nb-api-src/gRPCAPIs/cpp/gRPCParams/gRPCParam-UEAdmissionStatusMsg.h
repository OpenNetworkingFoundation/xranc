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

#ifndef _GRPCPARAM_UEADMISSIONSTATUSMSG_
#define _GRPCPARAM_UEADMISSIONSTATUSMSG_

#include <iostream>
#include <vector>

#include "gRPCParam-ProceduralMsg.h"
#include "gRPCSubParam-ECGIMsg.h"

class gRPCParamUEAdmissionStatusMsg : public gRPCParamProceduralMsg {

    public:
        gRPCParamUEAdmissionStatusMsg();
        gRPCParamUEAdmissionStatusMsg(std::string crnti, std::string plmnid, std::string ecid);
        ~gRPCParamUEAdmissionStatusMsg();
        std::string getCrnti();
        void setCrnti(std::string crnti);
        gRPCSubParamECGIMsg getEcgi();
        void setEcgi(std::string plmnId, std::string ecid);
        void setEcgi(gRPCSubParamECGIMsg ecgi);
        std::string getAdmissionEstStatus();
        void setAdmissionEstStatus(std::string admissionEstStatus);

    private:
        std::string crnti;
        gRPCSubParamECGIMsg ecgi;
        std::string admissionEstStatus;

    protected:
};

std::ostream& operator<<(std::ostream& os, gRPCParamUEAdmissionStatusMsg ueAdmissionStatusMsg);

#endif /* _GRPCPARAM_UEADMISSIONSTATUSMSG_ */