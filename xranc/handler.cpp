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
#include "config.h"

#include <gRPCAPIs/cpp/gRPCPB/gRPC-UEAdmissionStatus.grpc.pb.h>
#include <gRPCAPIs/cpp/gRPCPB/gRPC-UEContextUpdate.grpc.pb.h>
#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-UEAdmissionStatusMsg.h>
#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-UEContextUpdateMsg.h>
#include "gRPCHandlers/gRPCClientImpls/gRPCClientImpl-UEAdmissionStatus.h"
#include "gRPCHandlers/gRPCClientImpls/gRPCClientImpl-UEContextUpdate.h"


void copy_crnti(CRNTI_t *dest, CRNTI_t *src) {
    dest->buf = (uint8_t *)calloc(1, src->size);
    memcpy(dest->buf, src->buf, src->size);
    dest->size = src->size;
}

void copy_ecgi(ECGI_t *dest, ECGI_t *src) {
    dest->pLMN_Identity.buf = (uint8_t *)calloc(1, src->pLMN_Identity.size);
    memcpy(dest->pLMN_Identity.buf, src->pLMN_Identity.buf, src->pLMN_Identity.size);
    dest->pLMN_Identity.size = src->pLMN_Identity.size;
    dest->eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, src->eUTRANcellIdentifier.size);
    memcpy(dest->eUTRANcellIdentifier.buf, src->eUTRANcellIdentifier.buf, src->eUTRANcellIdentifier.size);
    dest->eUTRANcellIdentifier.size = src->eUTRANcellIdentifier.size;
}

void copy_erab_response(ERABResponse_t *dest, ERABResponse_t *src) {
    // TODO
}

void ue_admission_request(XRANCPDU *pdu, client_t *client) {

    log_debug("-> UEAdmReq enodeb:{} crnti:{}",
                pdu->body.choice.uEAdmissionRequest.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionRequest.crnti.buf)));

    XRANCPDU *resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /* Fill in the version */
    resp->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));

    //Shad - add api version to config
    *(resp->hdr.ver.buf) = '5';
    resp->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    resp->hdr.api_id = XRANC_API_ID_uEAdmissionResponse;

    resp->body.present = XRANCPDUBody_PR_uEAdmissionResponse;

    // Shad - copy CRNTI from request ???
    copy_crnti(&resp->body.choice.uEAdmissionResponse.crnti,
            &pdu->body.choice.uEAdmissionResponse.crnti);

    //  Shad Copy over the ECGI from the request ???
    copy_ecgi(&resp->body.choice.uEAdmissionResponse.ecgi,
            &pdu->body.choice.uEAdmissionResponse.ecgi);

    resp->body.choice.uEAdmissionResponse.adm_est_response = AdmEstResponse_success;

    client_send(resp, client);

    client->num_ue_admissions++;

    log_debug("<- UEAdmResp enodeb:{} crnti:{}",
                resp->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(resp->body.choice.uEAdmissionResponse.crnti.buf)));

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);
}

void ue_admission_status(XRANCPDU *pdu, client_t *client) {

    Config* config = Config::Instance();
    std::string redisServerInfo = config->redis_ip_addr + ":" + GRPC_SB_UEADMSTAT_PORT;

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

    gRPCParamUEAdmissionStatusMsg ueAdmissionStatusMsg(recvCrnti, recvPlmnId, recvEcid);
    ueAdmissionStatusMsg.setAdmissionEstStatus(recvAdmissionEstStatus);

    log_debug("-> UEAdmStatus enodeb:{} crnti:{} ueAdmEstStatus:{}",
                pdu->body.choice.uEAdmissionStatus.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionStatus.crnti.buf)),
                std::to_string(body.adm_est_status));

    if (recvAdmissionEstStatus.compare("0")) { // ueAdmEststatus == 0 - successful
        gRPCClientImplUEAdmissionStatus reportService(grpc::CreateChannel(redisServerInfo, grpc::InsecureChannelCredentials()));
        int resultCode = reportService.UpdateUEAdmissionStatus(ueAdmissionStatusMsg);
        if (resultCode != 1) {
            log_warn("UEAdmissionStatus is not updated well due to a NBI connection problem");
        }
    }
}

void ue_context_update(XRANCPDU *pdu, client_t *client) {

    Config* config = Config::Instance();
    std::string redisServerInfo = config->redis_ip_addr + ":" + GRPC_SB_UECONTEXTUPDATE_PORT;

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

    gRPCParamUEContextUpdateMsg ueContext(recvImsi);
    ueContext.setEcgi(recvPlmnId, recvEcid);
    ueContext.setCrnti(recvCrnti);
    ueContext.setMmeUeS1apId(recvMmeUeS1apId);
    ueContext.setEnbUeS1apId(recvEnbUeS1apId);

    log_info("-> UEContextUpdate crnti:{} plmnid:{} ecid:{} mme_ue_s1ap_id:{} enb_ue_s1ap_id:{} imsi:{}", 
        recvCrnti, recvPlmnId, recvEcid, recvMmeUeS1apId, recvEnbUeS1apId, recvImsi);

    gRPCClientImplUEContextUpdate reportService(grpc::CreateChannel(redisServerInfo, grpc::InsecureChannelCredentials()));
    int resultCode = reportService.UpdateUEContext(ueContext);
    if (resultCode != 1) {
        log_warn("UEContextUpdate is not updated well due to a NBI connection problem");
    }
}

void bearer_admission_request(XRANCPDU *pdu, client_t *client) {
    XRANCPDU *resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /* Fill in the version */
    resp->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));

    //Shad - add api version to config
    *(resp->hdr.ver.buf) = '5';
    resp->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    resp->hdr.api_id = XRANC_API_ID_bearerAdmissionResponse;

    resp->body.present = XRANCPDUBody_PR_bearerAdmissionResponse;

    copy_crnti(&resp->body.choice.bearerAdmissionResponse.crnti,
            &pdu->body.choice.bearerAdmissionRequest.crnti);

    copy_ecgi(&resp->body.choice.bearerAdmissionResponse.ecgi,
            &pdu->body.choice.bearerAdmissionRequest.ecgi);

    resp->body.choice.bearerAdmissionResponse.num_erab_list
            = pdu->body.choice.bearerAdmissionRequest.num_erabs;

    int ret;
    ERABResponse_Item_t *erab_response;
    for (int i = 0; i < pdu->body.choice.bearerAdmissionRequest.num_erabs; i++) {
        erab_response = (ERABResponse_Item_t *)calloc(1, sizeof(ERABResponse_Item_t));
        assert(erab_response);
        erab_response->id = pdu->body.choice.bearerAdmissionRequest.erab_params.list.array[0]->id;
        erab_response->decision = 0;
        ret = ASN_SEQUENCE_ADD(&resp->body.choice.bearerAdmissionResponse.erab_response, erab_response);
        assert(ret == 0);
    }

    client_send(resp, client);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);
}

void bearer_admission_status(XRANCPDU *pdu, client_t *client) {
    // TODO
}

void bearer_release_ind(XRANCPDU *pdu, client_t *client) {
    // TODO
}
