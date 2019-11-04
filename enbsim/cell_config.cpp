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
#include "context.h"
#include "config.h"

void copy_ecgi(ECGI_t *dest, ECGI_t *src) {
    dest->pLMN_Identity.buf = (uint8_t *)calloc(1, sizeof(PLMN_Identity_t));
    memcpy(dest->pLMN_Identity.buf, src->pLMN_Identity.buf, src->pLMN_Identity.size);
    dest->pLMN_Identity.size = src->pLMN_Identity.size;
    dest->eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, src->eUTRANcellIdentifier.size);
    memcpy(dest->eUTRANcellIdentifier.buf, src->eUTRANcellIdentifier.buf, src->eUTRANcellIdentifier.size);
    dest->eUTRANcellIdentifier.size = src->eUTRANcellIdentifier.size;
}

void cell_config_request(XRANCPDU *req, context_t *ctx) {
    // TODO
	asn_enc_rval_t er;
    XRANCPDU *resp;
    struct Cell cell;
    int ret;

    Config* config = Config::Instance();

    /*  Allocate an instance of XRANCPDU */
    resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));

    /* Fill in the version */
    resp->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));
    //Shad - add api version to config
    *(resp->hdr.ver.buf) = '5';
    resp->hdr.ver.size = sizeof(char);

    /* Fill in the API Id */
    resp->hdr.api_id = XRANC_API_ID_cellConfigReport;

    resp->body.present = XRANCPDUBody_PR_cellConfigReport;

    /*  FIXME - Copy PLMN Id and eUTRAN cell id from request */
    copy_ecgi(&resp->body.choice.cellConfigReport.ecgi,
            &req->body.choice.cellConfigRequest.ecgi);

    /*  Physical cell id */
    resp->body.choice.cellConfigReport.pci = 1;
    {
        CandScell_t *cand_scell = (CandScell_t *)calloc(1, sizeof(CandScell_t));
        cand_scell->pci = 51;
        cand_scell->earfcn_dl = 51;
        ret = ASN_SEQUENCE_ADD(&resp->body.choice.cellConfigReport.cand_scells, cand_scell);
        assert(ret == 0);
    }
    resp->body.choice.cellConfigReport.earfcn_dl = 51;
    resp->body.choice.cellConfigReport.earfcn_ul = 38000;
    resp->body.choice.cellConfigReport.rbs_per_tti_dl = 40;
    resp->body.choice.cellConfigReport.rbs_per_tti_ul = 40;
    resp->body.choice.cellConfigReport.num_tx_antenna = 2;
    resp->body.choice.cellConfigReport.duplex_mode = DuplexMode_tdd;
    resp->body.choice.cellConfigReport.max_num_connected_ues = 1000;
    resp->body.choice.cellConfigReport.max_num_connected_bearers = 2000;
    resp->body.choice.cellConfigReport.max_num_ues_sched_per_tti_dl = 10;
    resp->body.choice.cellConfigReport.max_num_ues_sched_per_tti_ul = 10;
    resp->body.choice.cellConfigReport.dlfs_sched_enable = true;

    xer_fprint(stdout, &asn_DEF_XRANCPDU, resp);

    context_send(resp, ctx);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);
}
