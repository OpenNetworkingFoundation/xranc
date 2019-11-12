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

#ifndef _GRPCSUBPARAM_ECGIMSG_
#define _GRPCSUBPARAM_ECGIMSG_

#include <iostream>

#include "gRPCSubParam-Msg.h"

class gRPCSubParamECGIMsg : public gRPCSubParamMsg {

    public:
        gRPCSubParamECGIMsg();
        gRPCSubParamECGIMsg(std::string plmnId, std::string ecid);
        ~gRPCSubParamECGIMsg();
        std::string getGRPCSubParamString();
        std::string getPlmnId();
        void setPlmnId(std::string plmnId);
        std::string getEcid();
        void setEcid(std::string ecid);
    
    private:
        std::string plmnId;
        std::string ecid;

    protected:


};

#endif /* _GRPCSUBPARAM_ECGIMSG_ */