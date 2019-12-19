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

#include "gRPCParam-UEAdmissionStatusMsg.h"

gRPCParamUEAdmissionStatusMsg::gRPCParamUEAdmissionStatusMsg() {
    this->xRANProceduralMsgType = ADMISSION_CONTROL;
}

gRPCParamUEAdmissionStatusMsg::gRPCParamUEAdmissionStatusMsg(std::string crnti, std::string plmnid, std::string ecid) {
    this->xRANProceduralMsgType = ADMISSION_CONTROL;
    this->crnti = crnti;
    this->ecgi = gRPCSubParamECGIMsg(plmnid, ecid);
}

gRPCParamUEAdmissionStatusMsg::~gRPCParamUEAdmissionStatusMsg() {}

std::string
gRPCParamUEAdmissionStatusMsg::getCrnti() {
    return crnti;
}

void
gRPCParamUEAdmissionStatusMsg::setCrnti(std::string crnti) {
    this->crnti = crnti;
}

gRPCSubParamECGIMsg
gRPCParamUEAdmissionStatusMsg::getEcgi() {
    return ecgi;
}

void
gRPCParamUEAdmissionStatusMsg::setEcgi(std::string plmnId, std::string ecid) {
    this->ecgi = gRPCSubParamECGIMsg(plmnId, ecid);
}
void
gRPCParamUEAdmissionStatusMsg::setEcgi(gRPCSubParamECGIMsg ecgi) {
    this->ecgi = gRPCSubParamECGIMsg(ecgi.getPlmnId(), ecgi.getEcid());
}

std::string
gRPCParamUEAdmissionStatusMsg::getAdmissionEstStatus() {
    return admissionEstStatus;
}

void
gRPCParamUEAdmissionStatusMsg::setAdmissionEstStatus(std::string admissionEstStatus) {
    this->admissionEstStatus = admissionEstStatus;
}