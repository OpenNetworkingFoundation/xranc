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

#include "gRPCParam-UEContextUpdateMsg.h"

gRPCParamUEContextUpdateMsg::gRPCParamUEContextUpdateMsg() {
    this->xRANProceduralMsgType = ADMISSION_CONTROL;
}

gRPCParamUEContextUpdateMsg::gRPCParamUEContextUpdateMsg(std::string imsi) {
    this->xRANProceduralMsgType = ADMISSION_CONTROL;
    this->imsi = imsi;
}

gRPCParamUEContextUpdateMsg::~gRPCParamUEContextUpdateMsg() {}

gRPCSubParamECGIMsg
gRPCParamUEContextUpdateMsg::getEcgi() {
    return ecgi;
}

void
gRPCParamUEContextUpdateMsg::setEcgi(std::string plmnId, std::string ecid) {
    this->ecgi = gRPCSubParamECGIMsg(plmnId, ecid);
}

void
gRPCParamUEContextUpdateMsg::setEcgi(gRPCSubParamECGIMsg ecgi) {
    this->ecgi = gRPCSubParamECGIMsg(ecgi.getPlmnId(), ecgi.getEcid());
}

std::string
gRPCParamUEContextUpdateMsg::getCrnti() {
    return crnti;
}

void
gRPCParamUEContextUpdateMsg::setCrnti(std::string crnti) {
    this->crnti = crnti;
}

std::string
gRPCParamUEContextUpdateMsg::getMmeUeS1apId() {
    return mmeUeS1apId;
}

void
gRPCParamUEContextUpdateMsg::setMmeUeS1apId(std::string mmeUeS1apId) {
    this->mmeUeS1apId = mmeUeS1apId;
}

std::string
gRPCParamUEContextUpdateMsg::getEnbUeS1apId() {
    return enbUeS1apId;
}

void
gRPCParamUEContextUpdateMsg::setEnbUeS1apId(std::string enbUeS1apId) {
    this->enbUeS1apId = enbUeS1apId;
}

std::string
gRPCParamUEContextUpdateMsg::getImsi() {
    return imsi;
}

void
gRPCParamUEContextUpdateMsg::setImsi(std::string imsi) {
    this->imsi = imsi;
}