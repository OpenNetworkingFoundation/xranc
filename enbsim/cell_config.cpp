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
#include "asn.h"

void cell_config_request(XRANCPDU *req, context_t *context) {
    struct Cell cell;
    int ret;
    XRANCPDU *resp = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    XRAN_HEADER (req, cellConfigReport);
    XRAN_ECGI (req, cellConfigReport, context->enb_index);

    log_debug("<- CCReq enodeb:{}", context->enb_index);

    resp->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char));
    *(resp->hdr.ver.buf) = '5';
    resp->hdr.ver.size = sizeof(char);
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

    ctx_send(resp, context);

    log_debug("-> CCResp enodeb:{}", context->enb_index);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, resp);
}
