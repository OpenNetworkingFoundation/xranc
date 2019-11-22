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

void ue_admission_request(context_t *context, uint16_t crnti) {
    char *req_buf = (char *)malloc(4096);
    int req_buf_size = 4096;
    XRANCPDU *req = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    int nbytes = 0;

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

    //xer_fprint(stdout, &asn_DEF_XRANCPDU, req);

    asn_enc_rval_t er = asn_encode_to_buffer(0, ATS_BER, &asn_DEF_XRANCPDU, req, req_buf, req_buf_size);
    if(er.encoded > req_buf_size) {
       fprintf(stderr, "Buffer of size %d is too small for %s, need %zu\n",
           req_buf_size, asn_DEF_XRANCPDU.name, er.encoded);
    }

    nbytes = er.encoded;

    if (nbytes) {
//        struct evbuffer *tmp = evbuffer_new();
//        evbuffer_add(tmp, req_buf, nbytes);
        if (bufferevent_write(context->buf_ev, req_buf, nbytes)) {
            printf("Error sending data to context on fd %d\n", context->fd);
        }
//        evbuffer_free(tmp);
    }

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req);

    //printf("-> UEAdmReq %d %d\n", crnti, nbytes);
}

void ue_admission_response(XRANCPDU *pdu, context_t *context) {
    uint16_t crnti;

    crnti = ntohs(*((uint16_t *)(pdu->body.choice.uEAdmissionResponse.crnti.buf)));

    //printf("<- UEAdmResp %d\n", crnti);
}

void start_ues(context_t *context) {

    for (int i = 0; i < context->num_ues; i++) {
	sleep(1);
        ue_admission_request(context, i + 1);
    }
}
