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
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>

#include <arpa/inet.h>
#include <XRANCPDU.h>
#include <CRNTI.h>
#include "client.h"
#include "logger.h"
#include "asn.h"
#include "config.h"

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "api/e2-interface/e2-interface.grpc.pb.h"
#include "api/e2-interface/gRPCClientE2Interface.h"

void ue_admission_request(XRANCPDU *pdu, client_t *client) {

    uint16_t crnti = ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionRequest.crnti.buf));

    log_debug("<- UEAdmReq enodeb:{} crnti:{}",
                pdu->body.choice.uEAdmissionRequest.ecgi.eUTRANcellIdentifier.buf[2],
                crnti);

    XRANCPDU *resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (resp, uEAdmissionResponse);
    XRAN_CRNTI (resp, uEAdmissionResponse, crnti);
    XRAN_ECGI (resp, uEAdmissionResponse, client->enb_index);

    resp->body.choice.uEAdmissionResponse.adm_est_response = AdmEstResponse_success;

    client_send(resp, client);

    client->num_ue_admissions++;

    log_debug("-> UEAdmResp enodeb:{} crnti:{}",
                resp->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(resp->body.choice.uEAdmissionResponse.crnti.buf)));

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);
}

void ue_admission_status(XRANCPDU *pdu, client_t *client) {

    Config* config = Config::Instance();
    std::string redisServerInfo = config->api_gw_ip_addr + ":" + std::to_string(config->api_gw_sbbundle_port);

    XRANCPDUBody_t payload = pdu->body;
    UEAdmissionStatus_t body = payload.choice.uEAdmissionStatus;

    // crnti
    std::string recvCrnti = std::to_string(ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionStatus.crnti.buf)));

    // ecgi
    std::string recvPlmnId;
    for(uint index = 0; index < body.ecgi.pLMN_Identity.size; index++) {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(body.ecgi.pLMN_Identity.buf[index]);
        recvPlmnId += stream.str();
    }
    //ECID
    std::string recvEcid;
    for (uint index = 0 ; index < body.ecgi.eUTRANcellIdentifier.size; index++) {
        for (int bitLoopIndex = 7; bitLoopIndex >= 0; bitLoopIndex--) {
            recvEcid += ((body.ecgi.eUTRANcellIdentifier.buf[index] >> bitLoopIndex) & 1) ? "1" : "0";
        }
    }

    // admissionEstStatus
    std::string recvAdmissionEstStatus = std::to_string(body.adm_est_status);

    interface::e2::E2ECGI* tmpECGI = new interface::e2::E2ECGI();
    tmpECGI->set_plmnid(recvPlmnId);
    tmpECGI->set_ecid(recvEcid);

    interface::e2::E2UEAdmissionStatusAttribute* tmpE2UEAdmissionStatusAttribute = new interface::e2::E2UEAdmissionStatusAttribute();
    tmpE2UEAdmissionStatusAttribute->set_crnti(recvCrnti);
    tmpE2UEAdmissionStatusAttribute->set_allocated_ecgi(tmpECGI);

    interface::e2::E2MessagePayload* tmpE2MessagePayload = new interface::e2::E2MessagePayload();
    tmpE2MessagePayload->set_allocated_ueadmissionstatusattribute(tmpE2UEAdmissionStatusAttribute);

    interface::e2::E2MessageHeader* tmpE2MessageHeader = new interface::e2::E2MessageHeader();
    tmpE2MessageHeader->set_messagetype(interface::e2::E2MessageType::E2_UEADMISSIONSTATUS);
    tmpE2MessageHeader->set_sourceid("enb");
    tmpE2MessageHeader->set_destinationid("redis");

    interface::e2::E2Message tmpE2Message;
    tmpE2Message.set_allocated_header(tmpE2MessageHeader);
    tmpE2Message.set_allocated_payload(tmpE2MessagePayload);

    log_debug("-> UEAdmStatus enodeb:{} crnti:{} ueAdmEstStatus:{}",
                pdu->body.choice.uEAdmissionStatus.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionStatus.crnti.buf)),
                std::to_string(body.adm_est_status));

    if (recvAdmissionEstStatus.compare("0")) { // ueAdmEststatus == 0 - successful
        gRPCClientE2Interface reportService(grpc::CreateChannel(redisServerInfo, grpc::InsecureChannelCredentials()));
        int resultCode = reportService.UpdateAttribute(tmpE2Message);
        if (resultCode == -1) {
            log_warn("UEAdmissionStatus is not updated well due to a NBI connection problem");
        }
    }
}

void ue_context_update(XRANCPDU *pdu, client_t *client) {

    Config* config = Config::Instance();
    std::string redisServerInfo = config->api_gw_ip_addr + ":" + std::to_string(config->api_gw_sbbundle_port);

    XRANCPDUBody_t payload = pdu->body;
    UEContextUpdate_t body = payload.choice.uEContextUpdate;

    // crnti
    std::string recvCrnti = std::to_string(ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionStatus.crnti.buf)));

    // ecgi
    // plmnid
    std::string recvPlmnId;
    for(uint index = 0; index < body.ecgi.pLMN_Identity.size; index++) {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(body.ecgi.pLMN_Identity.buf[index]);
        recvPlmnId += stream.str();
    }
    //ECID
    std::string recvEcid;
    for (uint index = 0 ; index < body.ecgi.eUTRANcellIdentifier.size; index++) {
        for (int bitLoopIndex = 7; bitLoopIndex >= 0; bitLoopIndex--) {
            recvEcid += ((body.ecgi.eUTRANcellIdentifier.buf[index] >> bitLoopIndex) & 1) ? "1" : "0";
        }
    }

    // mme_ue_s1ap_id
    std::string recvMmeUeS1apId = std::to_string(body.mME_UE_S1AP_ID);

    // enb_ue_s1ap_id
    std::string recvEnbUeS1apId = std::to_string(body.eNB_UE_S1AP_ID);

    // imsi
    std::string recvImsi;
    for (uint index = 0; index < body.imsi->size; index++) {
        recvImsi += body.imsi->buf[index];
    }

    interface::e2::E2ECGI* tmpECGI = new interface::e2::E2ECGI();
    tmpECGI->set_plmnid(recvPlmnId);
    tmpECGI->set_ecid(recvEcid);

    interface::e2::E2UEContextUpdateAttribute* tmpE2UEContextUpdateAttribute = new interface::e2::E2UEContextUpdateAttribute();
    tmpE2UEContextUpdateAttribute->set_allocated_ecgi(tmpECGI);
    tmpE2UEContextUpdateAttribute->set_crnti(recvCrnti);
    tmpE2UEContextUpdateAttribute->set_mmeues1apid(recvMmeUeS1apId);
    tmpE2UEContextUpdateAttribute->set_enbues1apid(recvEnbUeS1apId);
    tmpE2UEContextUpdateAttribute->set_imsi(recvImsi);

    log_debug("-> UEContextUpdate enodeb:{} crnti:{} plmnid:{} ecid:{} mme_ue_s1ap_id:{} enb_ue_s1ap_id:{} imsi{}",
        pdu->body.choice.uEContextUpdate.ecgi.eUTRANcellIdentifier.buf[2], 
        recvCrnti, recvPlmnId, recvEcid, recvMmeUeS1apId, recvEnbUeS1apId, recvImsi);

    interface::e2::E2MessagePayload* tmpE2MessagePayload = new interface::e2::E2MessagePayload();
    tmpE2MessagePayload->set_allocated_uecontextupdateattribute(tmpE2UEContextUpdateAttribute);
    
    interface::e2::E2MessageHeader* tmpE2MessageHeader = new interface::e2::E2MessageHeader();
    tmpE2MessageHeader->set_messagetype(interface::e2::E2MessageType::E2_UECONTEXTUPDATE);
    tmpE2MessageHeader->set_sourceid("enb");
    tmpE2MessageHeader->set_destinationid("redis");

    interface::e2::E2Message tmpE2Message;
    tmpE2Message.set_allocated_header(tmpE2MessageHeader);
    tmpE2Message.set_allocated_payload(tmpE2MessagePayload);

    gRPCClientE2Interface reportService(grpc::CreateChannel(redisServerInfo, grpc::InsecureChannelCredentials()));
    int resultCode = reportService.UpdateAttribute(tmpE2Message);
    if (resultCode != 1) {
        log_warn("UEContextUpdate is not updated well due to a NBI connection problem");
    }
}
