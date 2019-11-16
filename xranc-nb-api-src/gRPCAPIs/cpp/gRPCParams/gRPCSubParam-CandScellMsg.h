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

#ifndef _GRPCSUBPARAM_CANDSCELLMSG_
#define _GRPCSUBPARAM_CANDSCELLMSG_

#include <iostream>

#include "gRPCSubParam-Msg.h"

class gRPCSubParamCandScellMsg : public gRPCSubParamMsg {
    
    public:
        gRPCSubParamCandScellMsg();
        gRPCSubParamCandScellMsg(std::string pci, std::string earfcnDl);
        ~gRPCSubParamCandScellMsg();
        std::string getGRPCSubParamString();
        std::string getPci();
        void setPci(std::string pci);
        std::string getEarfcnDl();
        void setEarfcnDl(std::string earfcnDl);

    private:
        std::string pci;
        std::string earfcnDl;

    protected:
};

#endif /* _GRPCSUBPARAM_CANDSCELLMSG_ */