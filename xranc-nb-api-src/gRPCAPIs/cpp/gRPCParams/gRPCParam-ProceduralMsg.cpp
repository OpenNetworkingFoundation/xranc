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

#include "gRPCParam-ProceduralMsg.h"

gRPCParamProceduralMsg::gRPCParamProceduralMsg() {
    this->xRANMessageType = PROCEDURAL_MESSAGES;
}

gRPCParamProceduralMsg::~gRPCParamProceduralMsg() {}

XRANProceduralMsgType
gRPCParamProceduralMsg::getXRANProceduralMsgType() {
    return xRANProceduralMsgType;
}

void
gRPCParamProceduralMsg::setXRANProceduralMsgType(XRANProceduralMsgType xRANProceduralMsgType) {
    this->xRANProceduralMsgType = xRANProceduralMsgType;
}

std::string
XRANProceduralMsgTypeAsString(XRANProceduralMsgType xRANProceduralMsgType) {
    std::string xRANProceduralMsgTypeStrings[] = {
        "UNKNOWN_CONFIGURATION_MESSAGE_TYPE",
        "ADMISSION_CONTROL",
        "HANDOVER_MANAGEMENT",
        "BEARER_MANAGEMENT"
    };

    return xRANProceduralMsgType < sizeof(xRANProceduralMsgTypeStrings)/sizeof(xRANProceduralMsgTypeStrings[0]) ?
        xRANProceduralMsgTypeStrings[xRANProceduralMsgType] : xRANProceduralMsgTypeStrings[0];
}

std::ostream&
operator<<(std::ostream& os, XRANProceduralMsgType xRANProceduralMsgType) {
    return os << XRANProceduralMsgTypeAsString(xRANProceduralMsgType);
}
