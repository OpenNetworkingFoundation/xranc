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

#include "gRPCClientImpl-CellConfigReport.h"

int
gRPCClientImplCellConfigReport::UpdateCellConfig(gRPCParamCellConfigReportMsg cellConfigReportMsg) {
    gMsgECGI* ecgi = new gMsgECGI();
    ecgi->set_plmnid(cellConfigReportMsg.getEcgi().getPlmnId());
    ecgi->set_ecid(cellConfigReportMsg.getEcgi().getEcid());

    gMsgCellConfigValues cellConfigValues; //input
    cellConfigValues.set_allocated_ecgi(ecgi);
    cellConfigValues.set_pci(cellConfigReportMsg.getPci());
    for (int index = 0; index < cellConfigReportMsg.getCandScells().size(); index++) {
        gMsgCandScell* candScell = cellConfigValues.add_candscells();
        candScell->set_pci(cellConfigReportMsg.getCandScells().at(index).getPci());
        candScell->set_earfcndl(cellConfigReportMsg.getCandScells().at(index).getEarfcnDl());
    }
    cellConfigValues.set_earfcndl(cellConfigReportMsg.getEarfcnDl());
    cellConfigValues.set_earfcnul(cellConfigReportMsg.getEarfcnUl());
    cellConfigValues.set_rbsperttidl(cellConfigReportMsg.getRbsPerTtiDl());
    cellConfigValues.set_rbsperttiul(cellConfigReportMsg.getRbsPerTtiUl());
    cellConfigValues.set_numtxantenna(cellConfigReportMsg.getNumTxAntenna());
    cellConfigValues.set_duplexmode(cellConfigReportMsg.getDuplexMode());
    cellConfigValues.set_maxnumconnectedues(cellConfigReportMsg.getMaxNumConnectedUes());
    cellConfigValues.set_maxnumconnectedbearers(cellConfigReportMsg.getMaxNumConnectedBearers());
    cellConfigValues.set_maxnumuesschedperttidl(cellConfigReportMsg.getMaxNumUesSchedPerTtiDl());
    cellConfigValues.set_maxnumuesschedperttiul(cellConfigReportMsg.getMaxNumUesSchedPerTtiUl());
    cellConfigValues.set_dlfsschedenable(cellConfigReportMsg.getDlfsSchedEnable());

    gMsgResults results;
    ClientContext context;

    CompletionQueue cq;

    Status status;

    std::unique_ptr<ClientAsyncResponseReader<gMsgResults>> rpc(stub_->PrepareAsyncUpdateCellConfig(&context, cellConfigValues, &cq));

    rpc->StartCall();

    rpc->Finish(&results, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    if (status.ok()) {
        return 1;
    } else {
        return 0;
    }

    //delete variables
    delete ecgi;
    cellConfigValues.clear_candscells();
}
