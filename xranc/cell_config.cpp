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
#include <sstream>
#include <iomanip>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "api/e2-interface/e2-interface.grpc.pb.h"
#include "api/e2-interface/gRPCClientE2Interface.h"

#include "logger.h"
#include "asn.h"

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
    XRANCPDU *pdu = (XRANCPDU *)calloc(1, sizeof(XRANCPDU));
    struct Cell cell;

    log_debug("-> CCReq enodeb:{}", client->enb_index);

    XRAN_HEADER (pdu, cellConfigRequest);

    pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.buf = (uint8_t *)calloc(1, 3);
    pdu->body.choice.cellConfigRequest.ecgi.pLMN_Identity.size = 3;
    pdu->body.choice.cellConfigRequest.ecgi.eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, 4);
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

    Config* config = Config::Instance();
    std::string redisServerInfo = config->api_gw_ip_addr + ":" + std::to_string(config->api_gw_sbbundle_port);

    XRANCPDUBody_t payload = pdu->body;
    CellConfigReport_t body = payload.choice.cellConfigReport;
    // PLMN ID
    std::string recvPlmnId;
    for(uint index = 0; index < body.ecgi.pLMN_Identity.size; index++) {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(body.ecgi.pLMN_Identity.buf[index]);
        recvPlmnId += stream.str();
    }
    //ECID
    std::string recvEcid;
    for (uint index = 0 ; index < body.ecgi.eUTRANcellIdentifier.size; index++) {
        for (int bitLoopIndex = 7; bitLoopIndex >= 0; bitLoopIndex--) {
            recvEcid += ((body.ecgi.eUTRANcellIdentifier.buf[index] >> bitLoopIndex) & 1) ? "1" : "0";
        }
    }

    interface::e2::E2ECGI* tmpECGI = new interface::e2::E2ECGI();
    tmpECGI->set_plmnid(recvPlmnId);
    tmpECGI->set_ecid(recvEcid);

    interface::e2::E2CellConfigReportAttribute* tmpCellConfigReportAttribute = new interface::e2::E2CellConfigReportAttribute();
    tmpCellConfigReportAttribute->set_allocated_ecgi(tmpECGI);
    tmpCellConfigReportAttribute->set_pci(std::to_string(body.pci));
    for (int index = 0; index < body.cand_scells.list.count; index++) {
        interface::e2::E2CandScell* tmpCandScell = tmpCellConfigReportAttribute->add_candscells();
        tmpCandScell->set_pci(std::to_string(body.cand_scells.list.array[index]->pci));
        tmpCandScell->set_earfcndl(std::to_string(body.cand_scells.list.array[index]->earfcn_dl));
    }
    tmpCellConfigReportAttribute->set_earfcndl(std::to_string(body.earfcn_dl));
    tmpCellConfigReportAttribute->set_earfcnul(std::to_string(body.earfcn_ul));
    tmpCellConfigReportAttribute->set_rbsperttidl(std::to_string(body.rbs_per_tti_dl));
    tmpCellConfigReportAttribute->set_rbsperttiul(std::to_string(body.rbs_per_tti_ul));
    tmpCellConfigReportAttribute->set_numtxantenna(std::to_string(body.num_tx_antenna));
    tmpCellConfigReportAttribute->set_duplexmode(std::to_string(body.duplex_mode));
    tmpCellConfigReportAttribute->set_maxnumconnectedues(std::to_string(body.max_num_connected_ues));
    tmpCellConfigReportAttribute->set_maxnumconnectedbearers(std::to_string(body.max_num_connected_bearers));
    tmpCellConfigReportAttribute->set_maxnumuesschedperttidl(std::to_string(body.max_num_ues_sched_per_tti_dl));
    tmpCellConfigReportAttribute->set_maxnumuesschedperttiul(std::to_string(body.max_num_ues_sched_per_tti_ul));
    tmpCellConfigReportAttribute->set_dlfsschedenable(std::to_string(body.dlfs_sched_enable));

    interface::e2::E2MessagePayload* tmpE2MessagePayload = new interface::e2::E2MessagePayload();
    tmpE2MessagePayload->set_allocated_cellconfigattribute(tmpCellConfigReportAttribute);

    interface::e2::E2MessageHeader* tmpE2MessageHeader = new interface::e2::E2MessageHeader();
    tmpE2MessageHeader->set_messagetype(interface::e2::E2MessageType::E2_CELLCONFIGREPORT);
    tmpE2MessageHeader->set_sourceid("enb");
    tmpE2MessageHeader->set_destinationid("redis");
    
    interface::e2::E2Message tmpE2Message;
    tmpE2Message.set_allocated_header(tmpE2MessageHeader);
    tmpE2Message.set_allocated_payload(tmpE2MessagePayload);

    if (client->ecgi == NULL) {
        client->ecgi = (ecgi_t *)malloc(sizeof(ecgi_t));
        memcpy(client->ecgi->PLMN_Identity, body.ecgi.pLMN_Identity.buf, body.ecgi.pLMN_Identity.size);
        memcpy(client->ecgi->EUTRANCellIdentifier, body.ecgi.eUTRANcellIdentifier.buf, body.ecgi.eUTRANcellIdentifier.size);
        client->enb_index = body.ecgi.eUTRANcellIdentifier.buf[2];
        log_info("connected to enodeb:{}", client->enb_index);
    }

    log_debug("<- CCResp enodeb:{}", client->enb_index);

    delete_cell_config_timer(client);

    gRPCClientE2Interface reportService(grpc::CreateChannel(redisServerInfo, grpc::InsecureChannelCredentials()));
    int resultCode = reportService.UpdateAttribute(tmpE2Message);

    if (resultCode != 1) {
        log_warn("CellConfigReport is not updated well due to a NBI connection problem");
    }
}
