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

#include "gRPCSubParam-Msg.h"

gRPCSubParamMsg::gRPCSubParamMsg() {};

gRPCSubParamMsg::~gRPCSubParamMsg() {};

XRANParamType
gRPCSubParamMsg::getXRANParamType() {
    return xRANParamType;
}

void
gRPCSubParamMsg::setXRANParamType(XRANParamType xRANParamType) {
    this->xRANParamType = xRANParamType;
}

std::string
XRANParamTypeAsString(XRANParamType xRANParamType) {
    std::string xRANParamTypeStrings[] = {
        "UNKNOWN_XRAN_PARAM_TYPE",
        "XRAN_PARAM_ECGI",
        "XRAN_PARAM_CAND_SCELL"
    };
    return xRANParamType < sizeof(xRANParamTypeStrings)/sizeof(xRANParamTypeStrings[0]) ?
        xRANParamTypeStrings[xRANParamType] : xRANParamTypeStrings[0];
}

std::ostream&
operator<<(std::ostream& os, XRANParamType xRANParamType) {
    return os << XRANParamTypeAsString(xRANParamType);
}