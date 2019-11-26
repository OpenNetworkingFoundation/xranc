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
#include "logger.h"


/*  Test PLMN ID = Test MCC (001) + Test MNC (001) */
const uint8_t TEST_PLMNID[3] = {0x00, 0x10, 0x01};

static void make_ecgi(ECGI_t *dest, int enb_index) {
    dest->pLMN_Identity.buf = (uint8_t *)calloc(1, sizeof(PLMN_Identity_t));
    memcpy(dest->pLMN_Identity.buf, TEST_PLMNID, 3);
    dest->pLMN_Identity.size = 3;
    dest->eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, 4);
    dest->eUTRANcellIdentifier.buf[0] = 0;
    dest->eUTRANcellIdentifier.buf[1] = 0;
    dest->eUTRANcellIdentifier.buf[2] = enb_index;
    dest->eUTRANcellIdentifier.buf[3] = 0;
    dest->eUTRANcellIdentifier.size = 4;
}

int cell_config_request(XRANCPDU *req, char *resp_buf, int resp_buf_size, context_t *context) {
    // TODO
    XRANCPDU *resp;
    struct Cell cell;
    int ret;

    log_debug("<- CCReq enodeb:{}", context->enb_index);

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

    make_ecgi(&resp->body.choice.cellConfigReport.ecgi, context->enb_index);

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

    //xer_fprint(stdout, &asn_DEF_XRANCPDU, resp);

    asn_enc_rval_t er = asn_encode_to_buffer(0, ATS_BER, &asn_DEF_XRANCPDU, resp, resp_buf, resp_buf_size);
    if(er.encoded > resp_buf_size) {
       fprintf(stderr, "Buffer of size %d is too small for %s, need %zu\n",
           resp_buf_size, asn_DEF_XRANCPDU.name, er.encoded);
    }

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);

    log_debug("-> CCResp enodeb:{}", context->enb_index);

    return  er.encoded;
}
