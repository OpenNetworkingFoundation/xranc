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

#include "gRPCSubParam-CandScellMsg.h"

gRPCSubParamCandScellMsg::gRPCSubParamCandScellMsg() {
    this->xRANParamType = XRAN_PARAM_CAND_SCELL;
}

gRPCSubParamCandScellMsg::gRPCSubParamCandScellMsg(std::string pci, std::string earfcnDl) {
    this->xRANParamType = XRAN_PARAM_CAND_SCELL;
    this->pci = pci;
    this->earfcnDl = earfcnDl;
}

gRPCSubParamCandScellMsg::~gRPCSubParamCandScellMsg() {}

std::string
gRPCSubParamCandScellMsg::getGRPCSubParamString() {
    return "pci:" + pci + "+earfcn-dl:" + earfcnDl;
}

std::string
gRPCSubParamCandScellMsg::getPci() {
    return pci;
}

void
gRPCSubParamCandScellMsg::setPci(std::string pci) {
    this->pci = pci;
}

std::string
gRPCSubParamCandScellMsg::getEarfcnDl() {
    return earfcnDl;
}

void
gRPCSubParamCandScellMsg::setEarfcnDl(std::string earfcnDl) {
    this->earfcnDl = earfcnDl;
}