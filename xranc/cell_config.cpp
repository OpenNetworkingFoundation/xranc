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
#include <stdio.h>
#include <vector>
#include <event2/event.h>
#include <sys/types.h>
#include <XRANCPDU.h>
#include <CellConfigRequest.h>   /* CellConfigRequest ASN.1 type  */
#include "cell_config.h"
#include "client.h"
#include "config.h"
#include <memory>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <gRPCAPIs/cpp/gRPCPB/gRPC-CellConfigReport.grpc.pb.h>
#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-CellConfigReportMsg.h>
#include "gRPCHandlers/gRPCClientImpls/gRPCClientImpl-CellConfigReport.h"
#include <sstream>
#include <iomanip>

#include "logger.h"

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
    //uint8_t PLMN_Identity[3];
    //config->get_plmn_id(client->ip, PLMN_Identity);
    pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf = (uint8_t *)calloc(1, 3);
    //memcpy(pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf, PLMN_Identity, sizeof(PLMN_Identity)/sizeof(PLMN_Identity[0]));
    pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.size = 3;

    //uint8_t EUTRANCellIdentifier[4];
    //config->get_eci(client->ip, EUTRANCellIdentifier);
    pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, 4);
    //memcpy(pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf, EUTRANCellIdentifier, sizeof(EUTRANCellIdentifier)/sizeof(EUTRANCellIdentifier[0]));
    pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.size = 4;

    if (client->ecgi) {
        memcpy(pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf, client->ecgi->PLMN_Identity, 3);
        memcpy(pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf, client->ecgi->EUTRANCellIdentifier, 4);
    } else {
        memset(pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf, 0, 3);
        memset(pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf, 0, 4);
    }

    client_send(pdu, client);

    ASN_STRUCT_FREE(asn_DEF_XRANCPDU, pdu);
}

void cell_config_response(XRANCPDU *pdu, client_t *client) {
    // TODO - Update information on Redis DB through NBI - gRPC
    Config* config = Config::Instance();
    std::string redisServerInfo = config->redis_ip_addr + ":" + std::to_string(config->redis_port);

    XRANCPDUBody_t payload = pdu->body;
    CellConfigReport_t body = payload.choice.cellConfigReport;
    // PLMN ID
    std::string recvPlmnId;
    for(int index = 0; index < body.ecgi.pLMN_Identity.size; index++) {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(body.ecgi.pLMN_Identity.buf[index]);
        recvPlmnId += stream.str();
    }
    //ECID
    std::string recvEcid;
    for (int index = 0 ; index < body.ecgi.eUTRANcellIdentifier.size; index++) {
        for (int bitLoopIndex = 7; bitLoopIndex >= 0; bitLoopIndex--) {
            recvEcid += ((body.ecgi.eUTRANcellIdentifier.buf[index] >> bitLoopIndex) & 1) ? "1" : "0";
        }
    }

    gRPCParamCellConfigReportMsg cellConfigReport(recvPlmnId, recvEcid); // PLMN ID and ECID
    cellConfigReport.setPci(std::to_string(body.pci)); // PCI

    std::vector<gRPCSubParamCandScellMsg> tmpArr;
    for (int index = 0; index < body.cand_scells.list.count; index++) {
        gRPCSubParamCandScellMsg tmpgRPCSubParamCandScellMsg(std::to_string(body.cand_scells.list.array[index]->pci), std::to_string(body.cand_scells.list.array[index]->earfcn_dl));
        tmpArr.push_back(tmpgRPCSubParamCandScellMsg);
    }

    cellConfigReport.setCandScells(tmpArr);
    cellConfigReport.setEarfcnDl(std::to_string(body.earfcn_dl));
    cellConfigReport.setEarfcnUl(std::to_string(body.earfcn_ul));
    cellConfigReport.setRbsPerTtiDl(std::to_string(body.rbs_per_tti_dl));
    cellConfigReport.setRbsPerTtiUl(std::to_string(body.rbs_per_tti_ul));
    cellConfigReport.setNumTxAntenna(std::to_string(body.num_tx_antenna));
    cellConfigReport.setDuplexMode(std::to_string(body.duplex_mode));
    cellConfigReport.setMaxNumConnectedUes(std::to_string(body.max_num_connected_ues));
    cellConfigReport.setMaxNumConnectedBearers(std::to_string(body.max_num_connected_bearers));
    cellConfigReport.setMaxNumUesSchedPerTtiDl(std::to_string(body.max_num_ues_sched_per_tti_dl));
    cellConfigReport.setMaxNumUesSchedPerTtiUl(std::to_string(body.max_num_ues_sched_per_tti_ul));
    cellConfigReport.setDlfsSchedEnable(std::to_string(body.dlfs_sched_enable));

    if (client->ecgi == NULL) {
        client->ecgi = (ecgi_t *)malloc(sizeof(ecgi_t));
        memcpy(client->ecgi->PLMN_Identity, body.ecgi.pLMN_Identity.buf, body.ecgi.pLMN_Identity.size);
        memcpy(client->ecgi->EUTRANCellIdentifier, body.ecgi.eUTRANcellIdentifier.buf, body.ecgi.eUTRANcellIdentifier.size);
    }

    gRPCClientImplCellConfigReport reportService(grpc::CreateChannel(redisServerInfo, grpc::InsecureChannelCredentials()));
    int resultCode = reportService.UpdateCellConfig(cellConfigReport);
    if (resultCode != 1) {
        log_warn("CellConfigReport is not updated well due to a NBI connection problem");
    }
}
