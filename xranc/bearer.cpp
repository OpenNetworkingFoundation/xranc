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

void bearer_admission_request(XRANCPDU *pdu, client_t *client) {
    uint16_t crnti = ntohs(*(uint16_t *)(pdu->body.choice.bearerAdmissionRequest.crnti.buf));

    log_debug("<- bearerAdmissionRequest enodeb:{} crnti:{}",
                pdu->body.choice.bearerAdmissionRequest.ecgi.eUTRANcellIdentifier.buf[2],
                crnti);

    XRANCPDU *resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (resp, bearerAdmissionResponse);
    XRAN_CRNTI (resp, bearerAdmissionResponse, crnti);
    XRAN_ECGI (resp, bearerAdmissionResponse, client->enb_index);

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

    log_debug("-> bearerAdmissionResponse enodeb:{} crnti:{}",
                pdu->body.choice.bearerAdmissionResponse.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.bearerAdmissionResponse.crnti.buf)));
}

void bearer_admission_status(XRANCPDU *pdu, client_t *client) {
    log_debug("<- bearerAdmissionStatus enodeb:{} crnti:{}",
                pdu->body.choice.bearerAdmissionStatus.ecgi.eUTRANcellIdentifier.buf[2],
                ntohs(*(uint16_t *)(pdu->body.choice.bearerAdmissionStatus.crnti.buf)));
}

void bearer_release_ind(XRANCPDU *pdu, client_t *client) {
    // TODO
}
