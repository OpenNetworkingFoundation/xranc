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
#include "dispatch.h"
#include "context.h"
#include "cell_config.h"
#include "ue.h"

void dispatch(uint8_t *buffer, size_t buf_size, context_t *context) {
    XRANCPDU *req_pdu = 0;
    asn_dec_rval_t rval;

    int resp_buf_size = 4096;
    char resp_buf[resp_buf_size];
    int nbytes = 0;

    rval = asn_decode(0, ATS_BER, &asn_DEF_XRANCPDU, (void **)&req_pdu, buffer, buf_size);
    switch (rval.code) {
        case RC_OK:
            break;
        case RC_WMORE:
        case RC_FAIL:
        default:
            ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req_pdu);
            return;
    }

    xer_fprint(stdout, &asn_DEF_XRANCPDU, req_pdu);

    switch (req_pdu->hdr.api_id) {
        case XRANC_API_ID_cellConfigRequest:
            nbytes = cell_config_request(req_pdu, resp_buf, resp_buf_size, context);
            break;
/*
        case XRANC_API_ID_uEAdmissionRequest:
            ue_admission_request(pdu, context);
            break;
        case XRANC_API_ID_uEAdmissionStatus:
            ue_admission_status(pdu, context);
            break;
        case XRANC_API_ID_uEContextUpdate:
            ue_context_update(pdu, context);
            break;
        case XRANC_API_ID_bearerAdmissionRequest:
            bearer_admission_request(pdu, context);
            break;
        case XRANC_API_ID_bearerAdmissionStatus:
            bearer_admission_status(pdu, context);
            break;
        case XRANC_API_ID_bearerReleaseInd:
            bearer_release_ind(pdu, context);
            break;
*/
        default:
            printf("Message %lu not handled\n", req_pdu->hdr.api_id);
    }

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, req_pdu);

    if (nbytes) {
        struct evbuffer *tmp = evbuffer_new();
        evbuffer_add(tmp, resp_buf, nbytes);
        if (bufferevent_write_buffer(context->buf_ev, tmp)) {
            printf("Error sending data to context on fd %d\n", context->fd);
            closecontext(context);
        }
        evbuffer_free(tmp);
    }

    if (context->connected = false) {
        printf("starting ues\n");
        context->connected = true;

        start_ues(context);
    }
}
