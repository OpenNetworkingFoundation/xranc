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

#include <arpa/inet.h>
#include <XRANCPDU.h>
#include <CRNTI.h>
#include "client.h"
#include "logger.h"
#include "asn.h"

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
    log_debug("<- UEAdmStatus enodeb:{} crnti:{}",
                pdu->body.choice.uEAdmissionStatus.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.uEAdmissionStatus.crnti.buf)));
}

void ue_context_update(XRANCPDU *pdu, client_t *client) {
    log_debug("<- UEContextUpdate enodeb:{} crnti:{}",
                pdu->body.choice.uEContextUpdate.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.uEContextUpdate.crnti.buf)));
}
