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

#ifndef _GRPCPARAM_UECONTEXTUPDASTEMSG_
#define _GRPCPARAM_UECONTEXTUPDASTEMSG_

#include <iostream>
#include <vector>

#include "gRPCParam-ProceduralMsg.h"
#include "gRPCSubParam-ECGIMsg.h"

class gRPCParamUEContextUpdateMsg : public gRPCParamProceduralMsg {

    public:
        gRPCParamUEContextUpdateMsg();
        gRPCParamUEContextUpdateMsg(std::string imsi);
        ~gRPCParamUEContextUpdateMsg();
        std::string getImsi();
        void setImsi(std::string imsi);
        gRPCSubParamECGIMsg getEcgi();
        void setEcgi(std::string plmnId, std::string ecid);
        void setEcgi(gRPCSubParamECGIMsg ecgi);
        std::string getCrnti();
        void setCrnti(std::string);
        std::string getMmeUeS1apId();
        void setMmeUeS1apId(std::string mmeUeS1apId);
        std::string getEnbUeS1apId();
        void setEnbUeS1apId(std::string enbUeS1apId);

    private:
        std::string imsi;
        gRPCSubParamECGIMsg ecgi;
        std::string crnti;
        std::string mmeUeS1apId;
        std::string enbUeS1apId;

    protected:

};

std::ostream& operator<<(std::ostream& os, gRPCParamUEContextUpdateMsg ueContextUpdateMsg);

#endif /* _GRPCPARAM_UECONTEXTUPDASTEMSG_ */