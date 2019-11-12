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

#include "gRPCSubParam-ECGIMsg.h"

gRPCSubParamECGIMsg::gRPCSubParamECGIMsg() {
    this->xRANParamType = XRAN_PARAM_ECGI;
}

gRPCSubParamECGIMsg::gRPCSubParamECGIMsg(std::string plmnId, std::string ecid) {
    this->xRANParamType = XRAN_PARAM_ECGI;
    this->plmnId = plmnId;
    this->ecid = ecid;
}

gRPCSubParamECGIMsg::~gRPCSubParamECGIMsg() {}

std::string
gRPCSubParamECGIMsg::getGRPCSubParamString() {
    return "plmnID:" + plmnId + "+ECID:" + ecid;
}

std::string
gRPCSubParamECGIMsg::getPlmnId() {
    return plmnId;
}

void
gRPCSubParamECGIMsg::setPlmnId(std::string plmnId) {
    this->plmnId = plmnId;
}

std::string
gRPCSubParamECGIMsg::getEcid() {
    return ecid;
}

void
gRPCSubParamECGIMsg::setEcid(std::string ecid) {
    this->ecid = ecid;
}