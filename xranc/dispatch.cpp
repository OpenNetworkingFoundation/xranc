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
#include "client.h"
#include "cell_config.h"
#include "handler.h"

void dispatch(uint8_t *buffer, size_t buf_size, client_t *client) {
    XRANCPDU *pdu = 0;
    asn_dec_rval_t rval;
    rval = asn_decode(0, ATS_BER, &asn_DEF_XRANCPDU, (void **)&pdu, buffer, buf_size);
    switch (rval.code) {
        case RC_OK:
            break;
        case RC_WMORE:
        case RC_FAIL:
        default:
            ASN_STRUCT_FREE(asn_DEF_XRANCPDU, pdu);
            return;
    }

    xer_fprint(stdout, &asn_DEF_XRANCPDU, pdu);

    switch (pdu->hdr.api_id) {
        case XRANC_API_ID_cellConfigReport:
            cell_config_response(pdu);
            break;
        case XRANC_API_ID_uEAdmissionRequest:
            ue_admission_request(pdu, client);
            break;
        case XRANC_API_ID_uEAdmissionStatus:
            ue_admission_status(pdu, client);
            break;
        case XRANC_API_ID_uEContextUpdate:
            ue_context_update(pdu, client);
            break;
        case XRANC_API_ID_bearerAdmissionRequest:
            bearer_admission_request(pdu, client);
            break;
        default:
            printf("Message %lu not handled\n", pdu->hdr.api_id);
    }

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, pdu);
}
