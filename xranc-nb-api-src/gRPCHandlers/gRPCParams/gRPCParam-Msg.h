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

#ifndef _GRPCPARAM_MSG_
#define _GRPCPARAM_MSG_

#include <iostream>

typedef enum {
    UNKNOWN_MESSAGE_TYPE=0,
    CONFIGURATION_MESSAGES,
    PROCEDURAL_MESSAGES,
    MEASUREMENTS,
    XICIC_RR_MGMT_CONTROL,
    CA_CONTROL,
    DUAL_CONN_CONTROL
} XRANMessageType;

class gRPCParamMsg {

    public:
        gRPCParamMsg();
        ~gRPCParamMsg();
        XRANMessageType getXRANMessageType();
        void setXRANMessageType(XRANMessageType xRANMessageType);

    private:

    protected:
        XRANMessageType xRANMessageType;

};

std::string XRANMessageTypeAsString(XRANMessageType xRANMessageType);
std::ostream& operator<<(std::ostream& os, XRANMessageType xRANMessageType); 

#endif /* _GRPCPARAM_MSG_ */