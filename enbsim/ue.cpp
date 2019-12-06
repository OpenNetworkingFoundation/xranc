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

#include <stdio.h>
#include <unistd.h>
#include <XRANCPDU.h>
#include "context.h"
#include "ue.h"
#include "asn_common.h"
#include "logger.h"

void ue_admission_request(context_t *context, uint16_t crnti) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /* Fill in the version */
    req->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));

    //Shad - add api version to config
    *(req->hdr.ver.buf) = '5';
    req->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    req->hdr.api_id = XRANC_API_ID_uEAdmissionRequest;

    req->body.present = XRANCPDUBody_PR_uEAdmissionRequest;

    req->body.choice.uEAdmissionRequest.crnti.buf = (uint8_t *)calloc(1, 2);
    req->body.choice.uEAdmissionRequest.crnti.size = 2;
    uint16_t htons_crnti = htons(crnti);
    memcpy(req->body.choice.uEAdmissionRequest.crnti.buf, &htons_crnti, 2);

    make_ecgi(&req->body.choice.uEAdmissionRequest.ecgi, context->enb_index);

    req->body.choice.uEAdmissionRequest.adm_est_cause = AdmEstCause_mo_signalling;

    ctx_send(req, context);

    log_debug("-> UEAdmReq enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);
}

void ue_admission_status(context_t *context, uint16_t crnti) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /* Fill in the version */
    req->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));

    //Shad - add api version to config
    *(req->hdr.ver.buf) = '5';
    req->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    req->hdr.api_id = XRANC_API_ID_uEAdmissionStatus;

    req->body.present = XRANCPDUBody_PR_uEAdmissionStatus;

    req->body.choice.uEAdmissionStatus.crnti.buf = (uint8_t *)calloc(1, 2);
    req->body.choice.uEAdmissionStatus.crnti.size = 2;
    uint16_t htons_crnti = htons(crnti);
    memcpy(req->body.choice.uEAdmissionStatus.crnti.buf, &htons_crnti, 2);

    make_ecgi(&req->body.choice.uEAdmissionStatus.ecgi, context->enb_index);

    req->body.choice.uEAdmissionStatus.adm_est_status = AdmEstStatus_success;

    ctx_send(req, context);

    log_debug("-> UEAdmStatus enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);
}

void ue_admission_response(XRANCPDU *pdu, context_t *context) {
    uint16_t crnti;

    crnti = ntohs(*((uint16_t *)(pdu->body.choice.uEAdmissionResponse.crnti.buf)));

    log_debug("<- UEAdmResp enodeb:{} crnti:{}", context->enb_index, crnti);

    ue_admission_status(context, crnti);
}

void start_ues(context_t *context) {

    for (int i = 0; i < context->num_ues; i++) {
        ue_admission_request(context, i + 1);
    }
}
