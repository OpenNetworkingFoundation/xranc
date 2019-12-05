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

#include <iostream>
#include <XRANCPDU.h>
#include "dispatch.h"
#include "context.h"
#include "cell_config.h"
#include "ue.h"
#include "logger.h"

using namespace std;

static size_t decode(XRANCPDU **pdu, uint8_t *buffer, size_t buf_size) {
    asn_dec_rval_t rval;
    rval = asn_decode(0, ATS_BER, &asn_DEF_XRANCPDU, (void **)pdu, buffer, buf_size);
    switch (rval.code) {
        case RC_OK:
            break;
        case RC_WMORE:
        case RC_FAIL:
        default:
            return 0;
    }

    return rval.consumed;
}

static void ue_admission_timeout(int fd, short event, void *arg)
{
    context_t *context = (context_t *)arg;
    log_info("starting ue admissions");
    start_ues(context);
    evtimer_del(context->ue_admission_timer);
}

void dispatch(uint8_t *buffer, size_t buf_size, context_t *context) {
    XRANCPDU *pdu = 0;

    int resp_buf_size = 4096;
    char resp_buf[resp_buf_size];
    int nbytes = 0;

    size_t remaining = buf_size;
    size_t consumed = 0;
    uint8_t *curr = buffer;

    do {
        consumed = decode(&pdu, curr, remaining);
        if (!consumed) {
            log_error("Error decoding input: remaining={}, consumed={}", remaining, consumed);
        }
        remaining -= consumed;
        curr += consumed;

        trace_pdu(pdu);

        switch (pdu->hdr.api_id) {
            case XRANC_API_ID_cellConfigRequest:
                nbytes = cell_config_request(pdu, resp_buf, resp_buf_size, context);
                break;
            case XRANC_API_ID_uEAdmissionResponse:
                ue_admission_response(pdu, context);
                break;
            default:
                printf("Message %lu not handled\n", pdu->hdr.api_id);
        }

        ASN_STRUCT_FREE(asn_DEF_XRANCPDU, pdu);
        pdu = 0;

        if (nbytes) {
            //struct evbuffer *tmp = evbuffer_new();
            //evbuffer_add(tmp, resp_buf, nbytes);
            if (bufferevent_write(context->buf_ev, resp_buf, nbytes)) {
                printf("Error sending data to context on fd %d\n", context->fd);
                closecontext(context);
            }
            //evbuffer_free(tmp);
        }
    } while (remaining);

    if (context->connected == false) {
        struct timeval tv = {1, 0};

        //printf("starting ues\n");
        log_info("starting ue admission timer");
        context->connected = true;

        context->ue_admission_timer = event_new(context->evbase, -1, EV_PERSIST, ue_admission_timeout, context);
        evtimer_add(context->ue_admission_timer, &tv);
    }
}
