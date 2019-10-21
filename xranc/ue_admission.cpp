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
/*
#include <stdio.h>
#include <vector>
#include <event2/event.h>
#include <sys/types.h>
#include <CellConfigRequest.h>
#include "cell_config.h"
#include "client.h"
#include "config.h"
*/

size_t ue_admission_request(XRANCPDU *pdu, client_t *client) {
	asn_enc_rval_t er;
    char buffer[4096];
    int buf_size = 4096;
    XRANCPDU resp;

    /*  Allocate an instance of XRANCPDU */

    /* Fill in the version */
    resp.hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));

    //Shad - add api version to config
    *(resp.hdr.ver.buf) = '5';
    resp.hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    resp.hdr.api_id = XRANC_API_ID_uEAdmissionResponse;

    resp.body.present = XRANCPDUBody_PR_uEAdmissionResponse;

    // Shad - copy from request - Is this the right thing to do?
    resp.body.choice.uEAdmissionResponse.crnti = pdu->body.choice.uEAdmissionResponse.crnti;
    resp.body.choice.uEAdmissionResponse.ecgi = pdu->body.choice.uEAdmissionResponse.ecgi;
    resp.body.choice.uEAdmissionResponse.adm_est_response = AdmEstResponse_success;

    xer_fprint(stdout, &asn_DEF_XRANCPDU, &resp);

	er = asn_encode_to_buffer(0, ATS_BER, &asn_DEF_XRANCPDU, &resp, buffer, buf_size);
    if(er.encoded > buf_size) {
       fprintf(stderr, "Buffer of size %d is too small for %s, need %zu\n",
           buf_size, asn_DEF_XRANCPDU.name, er.encoded);
    }

    struct evbuffer *tmp = evbuffer_new();
    evbuffer_add(tmp, buffer, buf_size);
    if (bufferevent_write_buffer(client->buf_ev, tmp)) {
        printf("Error sending data to client on fd %d\n", client->fd);
        closeClient(client);
    }
    evbuffer_free(tmp);

    return er.encoded;
}
