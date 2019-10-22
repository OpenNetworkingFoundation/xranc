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
#include <vector>
#include <event2/event.h>
#include <sys/types.h>
#include <XRANCPDU.h>
#include <CellConfigRequest.h>   /* CellConfigRequest ASN.1 type  */
#include "cell_config.h"
#include "client.h"
#include "config.h"

static void cell_config_timeout(int fd, short event, void *arg)
{
    cell_config_request((client_t *)arg);

}

void cell_config_timer_add(client_t *client) {
    Config* config = Config::Instance();
    struct timeval tv = {config->xranc_cellconfigrequest_interval_seconds, 0};

    client->cell_config_timer = event_new(client->evbase, -1, EV_PERSIST, cell_config_timeout, client);
    evtimer_add(client->cell_config_timer, &tv);
}

void cell_config_request(client_t *client) {
	asn_enc_rval_t er;
    XRANCPDU *pdu;
    struct Cell cell;

    Config* config = Config::Instance();

    /*  Allocate an instance of XRANCPDU */
    pdu = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /* Fill in the version */
    pdu->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));
    //Shad - add api version to config
    *(pdu->hdr.ver.buf) = '5';
    pdu->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    pdu->hdr.api_id = XRANC_API_ID_cellConfigRequest;

    pdu->body.present = XRANCPDUBody_PR_cellConfigRequest;

    /*  Fill in the ECGI */
    uint8_t PLMN_Identity[3];
    config->get_plmn_id(client->ip, PLMN_Identity);
    pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf = (uint8_t *)calloc(1, sizeof(PLMN_Identity)/sizeof(PLMN_Identity[0]));
    memcpy(pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf, PLMN_Identity, sizeof(PLMN_Identity)/sizeof(PLMN_Identity[0]));
    pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.size = sizeof(PLMN_Identity)/sizeof(PLMN_Identity[0]);

    uint8_t EUTRANCellIdentifier[4];
    config->get_eci(client->ip, EUTRANCellIdentifier);
    pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, sizeof(EUTRANCellIdentifier)/sizeof(EUTRANCellIdentifier[0]));
    memcpy(pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf, EUTRANCellIdentifier, sizeof(EUTRANCellIdentifier)/sizeof(EUTRANCellIdentifier[0]));
    pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.size = sizeof(EUTRANCellIdentifier)/sizeof(EUTRANCellIdentifier[0]);

    xer_fprint(stdout, &asn_DEF_XRANCPDU, pdu);

    client_send(pdu, client);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, pdu);
}

void cell_config_response(XRANCPDU *pdu) {
    // TODO
}
