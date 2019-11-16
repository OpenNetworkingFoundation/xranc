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

#include "gRPCParam-ConfigurationMsg.h"

gRPCParamConfigurationMsg::gRPCParamConfigurationMsg() {
    this->xRANMessageType = CONFIGURATION_MESSAGES;
}

gRPCParamConfigurationMsg::~gRPCParamConfigurationMsg() {}

XRANConfigurationMsgType
gRPCParamConfigurationMsg::getXRANConfigurationMsgType() {
    return xRANConfigurationMsgType;
}

void
gRPCParamConfigurationMsg::setXRANConfigurationMsgType(XRANConfigurationMsgType xRANConfigurationMsgType) {
    this->xRANConfigurationMsgType = xRANConfigurationMsgType;
}

std::string
XRANConfigurationMsgTypeAsString(XRANConfigurationMsgType xRANConfigurationMsgType) {
    std::string xRANConfigurationMsgTypeStrings[] = {
        "UNKNOWN_CONFIGURATION_MESSAGE_TYPE",
        "CELL_CONFIGURATION",
        "UE_CAPABILITY"
    };

    return xRANConfigurationMsgType < sizeof(xRANConfigurationMsgTypeStrings)/sizeof(xRANConfigurationMsgTypeStrings[0]) ?
        xRANConfigurationMsgTypeStrings[xRANConfigurationMsgType] : xRANConfigurationMsgTypeStrings[0];
}

std::ostream& operator<<(std::ostream& os, XRANConfigurationMsgType xRANConfigurationMsgType) {
    return os << XRANConfigurationMsgTypeAsString(xRANConfigurationMsgType);
}