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
#include <cstdlib>
#include <unistd.h>
#include <XRANCPDU.h>
#include "context.h"
#include "ue.h"
#include "asn.h"
#include "logger.h"

void ue_admission_request(context_t *context, uint16_t crnti) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (req, uEAdmissionRequest);
    XRAN_CRNTI (req, uEAdmissionRequest, crnti);
    XRAN_ECGI (req, uEAdmissionRequest, context->enb_index);

    req->body.choice.uEAdmissionRequest.adm_est_cause = AdmEstCause_mo_signalling;

    ctx_send(req, context);

    log_debug("-> UEAdmReq enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);
}

void bearer_admission_status(context_t *context, uint16_t crnti) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (req, bearerAdmissionStatus);
    XRAN_CRNTI (req, bearerAdmissionStatus, crnti);
    XRAN_ECGI (req, bearerAdmissionStatus, context->enb_index);

    BearerAdmissionStatus_t *x = &req->body.choice.bearerAdmissionStatus;

    x->num_erabs = 2;

    for (int i = 0; i < x->num_erabs; i++) {
        ERABResponse_Item_t *erab = (ERABResponse_Item_t *)calloc(1, sizeof(ERABResponse_Item_t));
        erab->id = i + 1;
        erab->decision = ERABDecision_success;
        int ret = ASN_SEQUENCE_ADD(&x->erab_status, erab);
        assert(ret == 0);
    }

    ctx_send(req, context);

    log_debug("-> bearerAdmissionStatus enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);
}

void bearer_admission_response(XRANCPDU *pdu, context_t *context) {
    uint16_t crnti;

    crnti = ntohs(*((uint16_t *)(pdu->body.choice.bearerAdmissionResponse.crnti.buf)));
    log_debug("<- bearerAdmissionResponse enodeb:{} crnti:{}", context->enb_index, crnti);

    bearer_admission_status(context, crnti);
}

void bearer_admission_request(context_t *context, uint16_t crnti) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (req, bearerAdmissionRequest);
    XRAN_CRNTI (req, bearerAdmissionRequest, crnti);
    XRAN_ECGI (req, bearerAdmissionRequest, context->enb_index);

    BearerAdmissionRequest_t *x = &req->body.choice.bearerAdmissionRequest;

    x->ue_ambr.ambr_dl.buf = (uint8_t *)calloc(1, sizeof(uint8_t));
    x->ue_ambr.ambr_dl.size = 1;
    *(x->ue_ambr.ambr_dl.buf) = 100;
    x->ue_ambr.ambr_ul.buf = (uint8_t *)calloc(1, sizeof(uint8_t));
    x->ue_ambr.ambr_ul.size = 1;
    *(x->ue_ambr.ambr_ul.buf) = 100;

    x->num_erabs = 2;

    for (int i = 0; i < x->num_erabs; i++) {
        ERABParams_Item_t *erab = (ERABParams_Item_t *)calloc(1, sizeof(ERABParams_Item_t));
        erab->id = i + 1;
        erab->direction = ERABDirection_ul;
        erab->type = ERABType_dedicated;
        erab->qci = 8;
        erab->arp = 5;
        erab->gbr_dl.buf = (uint8_t *)calloc(1, sizeof(uint16_t));
        erab->gbr_dl.size = sizeof(uint16_t);
        *((uint16_t *)(erab->gbr_dl.buf)) = htons(100);
        erab->gbr_ul.buf = (uint8_t *)calloc(1, sizeof(uint16_t));
        erab->gbr_ul.size = sizeof(uint16_t);
        *((uint16_t *)(erab->gbr_ul.buf)) = htons(200);
        erab->mbr_dl.buf = (uint8_t *)calloc(1, sizeof(uint16_t));
        erab->mbr_dl.size = sizeof(uint16_t);
        *((uint16_t *)(erab->mbr_dl.buf)) = htons(300);
        erab->mbr_ul.buf = (uint8_t *)calloc(1, sizeof(uint16_t));
        erab->mbr_ul.size = sizeof(uint16_t);
        *((uint16_t *)(erab->mbr_ul.buf)) = htons(400);
        int ret = ASN_SEQUENCE_ADD(&x->erab_params, erab);
        assert(ret == 0);
    }

    ctx_send(req, context);

    log_debug("-> bearerAdmissionRequest enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);
}

void ue_context_update(context_t *context, uint16_t crnti,
        uint32_t mme_ue_s1ap_id, uint32_t enb_ue_s1ap_id) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (req, uEContextUpdate);
    XRAN_CRNTI (req, uEContextUpdate, crnti);
    XRAN_ECGI (req, uEContextUpdate, context->enb_index);

    req->body.choice.uEContextUpdate.mME_UE_S1AP_ID = mme_ue_s1ap_id;
    req->body.choice.uEContextUpdate.eNB_UE_S1AP_ID = enb_ue_s1ap_id;

    req->body.choice.uEContextUpdate.imsi = (UTF8String_t *)calloc(1, sizeof(UTF8String_t));
    req->body.choice.uEContextUpdate.imsi->buf = (uint8_t *)calloc(1, 16);
    req->body.choice.uEContextUpdate.imsi->size = 15;
    memcpy(req->body.choice.uEContextUpdate.imsi->buf, "00101", 5);
    char *msin = (char *)calloc(1, 11);
    snprintf(msin, 11, "%010d", crnti);
    memcpy(req->body.choice.uEContextUpdate.imsi->buf + 5, msin, 10);
    free(msin);

    ctx_send(req, context);

    log_debug("-> UEContextUpdate enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);

    bearer_admission_request(context, crnti);
}

void ue_admission_status(context_t *context, uint16_t crnti) {
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (req, uEAdmissionStatus);
    XRAN_CRNTI (req, uEAdmissionStatus, crnti);
    XRAN_ECGI (req, uEAdmissionStatus, context->enb_index);

    req->body.choice.uEAdmissionStatus.adm_est_status = AdmEstStatus_success;

    ctx_send(req, context);

    log_debug("-> UEAdmStatus enodeb:{} crnti:{}", context->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);

    ue_context_update(context, crnti, crnti, crnti); //FIXME - using crnti as S1 AP ids
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
