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

#include <unistd.h>
#include "client.h"
#include "config.h"
#include "cell_config.h"
#include "logger.h"

void delete_cell_config_timer(client_t *client) {
    if (client->cell_config_timer != NULL) {
        evtimer_del(client->cell_config_timer);
        event_free(client->cell_config_timer);
        client->cell_config_timer = NULL;
    }

}
void closeClient(client_t *client) {
    if (client != NULL) {
        if (client->fd >= 0) {
            close(client->fd);
            client->fd = -1;
        }
        delete_cell_config_timer(client);
    }
}

void client_timers_add(client_t *client) {
    cell_config_timer_add(client);
}

void client_send(XRANCPDU *pdu, client_t *client) {
    asn_encode_to_new_buffer_result_t res = { NULL, {0, NULL, NULL} };

    trace_pdu(pdu);

    res = asn_encode_to_new_buffer(0, ATS_BER, &asn_DEF_XRANCPDU, pdu);

    if (bufferevent_write(client->buf_ev, res.buffer, res.result.encoded)) {
        log_error("ERROT sending data, fd {}", client->fd);
        closeClient(client);
    }
    free(res.buffer);
}
