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

#include <XRANCPDU.h>
#include "client.h"
#include "logger.h"
#include "asn.h"

void ho_request(client_t *client, uint16_t crnti) {
    XRANCPDU *pdu = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    pdu->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));
    *(pdu->hdr.ver.buf) = '5';
    pdu->hdr.ver.size = sizeof(char);
    pdu->hdr.api_id = XRANC_API_ID_hORequest;
    pdu->body.present = XRANCPDUBody_PR_hORequest;
    pdu->body.choice.hORequest.crnti.buf = (uint8_t *)calloc(1, sizeof(uint16_t));
    pdu->body.choice.hORequest.crnti.size = sizeof(uint16_t);
    *((uint16_t *)(pdu->body.choice.hORequest.crnti.buf)) = htons(crnti);
    make_ecgi(&pdu->body.choice.uEAdmissionStatus.ecgi, client->enb_index);

    client_send(pdu, client);

    log_debug("-> HOReq enodeb:{} crnti:{}", client->enb_index, crnti);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, pdu);
}
