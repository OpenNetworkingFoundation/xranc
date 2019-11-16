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

#ifndef _GRPCPARAM_CONFIGURATIONMSG_
#define _GRPCPARAM_CONFIGURATIONMSG_

#include <iostream>

#include "gRPCParam-Msg.h"

typedef enum {
    UNKNOWN_CONFIGURATION_MESSAGE_TYPE=0,
    CELL_CONFIGURATION,
    UE_CAPABILITY
} XRANConfigurationMsgType;

class gRPCParamConfigurationMsg : public gRPCParamMsg {

    public:
        gRPCParamConfigurationMsg();
        ~gRPCParamConfigurationMsg();
        XRANConfigurationMsgType getXRANConfigurationMsgType();
        void setXRANConfigurationMsgType(XRANConfigurationMsgType xRANConfigurationMsgType);

    private:

    protected:
        XRANConfigurationMsgType xRANConfigurationMsgType;
};

std::string XRANConfigurationMsgTypeAsString(XRANConfigurationMsgType xRANConfigurationMsgType);
std::ostream& operator<<(std::ostream& os, XRANConfigurationMsgType xRANConfigurationMsgType);

#endif /* _GRPCPARAM_CONFIGURATIONMSG_ */