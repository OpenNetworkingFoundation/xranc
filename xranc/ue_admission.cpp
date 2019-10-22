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

void ue_admission_request(XRANCPDU *pdu, client_t *client) {
    char buffer[4096];
    int buf_size = 4096;
    XRANCPDU *resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /*  Allocate an instance of XRANCPDU */

    /* Fill in the version */
    resp->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));

    //Shad - add api version to config
    *(resp->hdr.ver.buf) = '5';
    resp->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    resp->hdr.api_id = XRANC_API_ID_uEAdmissionResponse;

    resp->body.present = XRANCPDUBody_PR_uEAdmissionResponse;

    // Shad - copy CRNTI from request - Is this the right thing to do?
    resp->body.choice.uEAdmissionResponse.crnti.buf
        = (uint8_t *)calloc(1, pdu->body.choice.uEAdmissionResponse.crnti.size);
    memcpy(resp->body.choice.uEAdmissionResponse.crnti.buf,
            pdu->body.choice.uEAdmissionResponse.crnti.buf,
            pdu->body.choice.uEAdmissionResponse.crnti.size);
    resp->body.choice.uEAdmissionResponse.crnti.size
        = pdu->body.choice.uEAdmissionResponse.crnti.size;

    /*  Copy over the ECGI from the request */
    /*  Shad - not OK? */
    resp->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.buf
        = (uint8_t *)calloc(1, pdu->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.size);
    memcpy(resp->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.buf,
            pdu->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.buf,
            pdu->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.size);
    resp->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.size
        = pdu->body.choice.uEAdmissionResponse.ecgi.pLMN_Identity.size;

    resp->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.buf
        = (uint8_t *)calloc(1, pdu->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.size);
    memcpy(resp->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.buf,
            pdu->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.buf,
            pdu->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.size);
    resp->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.size
        = pdu->body.choice.uEAdmissionResponse.ecgi.eUTRANcellIdentifier.size;

    resp->body.choice.uEAdmissionResponse.adm_est_response = AdmEstResponse_success;

    xer_fprint(stdout, &asn_DEF_XRANCPDU, resp);

    client_send(resp, client);

    // Shad - seg faults if resp is free-ed up!!!
    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);
}
