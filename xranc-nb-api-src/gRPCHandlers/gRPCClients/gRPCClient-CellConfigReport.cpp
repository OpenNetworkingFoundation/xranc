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

#include "gRPCClient-CellConfigReport.h"

int
gRPCClientCellConfigReport::UpdateCellConfig(gRPCParamCellConfigReportMsg cellConfigReport) {

    gMsgECGI* ecgi = new gMsgECGI();
    ecgi->set_plmnid(cellConfigReport.getEcgi().getPlmnId());
    ecgi->set_ecid(cellConfigReport.getEcgi().getEcid());

    gMsgCellConfigValues cellConfigValues; //input
    cellConfigValues.set_allocated_ecgi(ecgi);
    cellConfigValues.set_pci(cellConfigReport.getPci());
    for (int index = 0; index < cellConfigReport.getCandScells().size(); index++) {
        gMsgCandScell* candScell = cellConfigValues.add_candscells();
        candScell->set_pci(cellConfigReport.getCandScells().at(index).getPci());
        candScell->set_earfcndl(cellConfigReport.getCandScells().at(index).getEarfcnDl());
    }
    cellConfigValues.set_earfcndl(cellConfigReport.getEarfcnDl());
    cellConfigValues.set_earfcnul(cellConfigReport.getEarfcnUl());
    cellConfigValues.set_rbsperttidl(cellConfigReport.getRbsPerTtiDl());
    cellConfigValues.set_rbsperttiul(cellConfigReport.getRbsPerTtiUl());
    cellConfigValues.set_numtxantenna(cellConfigReport.getNumTxAntenna());
    cellConfigValues.set_duplexmode(cellConfigReport.getDuplexMode());
    cellConfigValues.set_maxnumconnectedues(cellConfigReport.getMaxNumConnectedUes());
    cellConfigValues.set_maxnumconnectedbearers(cellConfigReport.getMaxNumConnectedBearers());
    cellConfigValues.set_maxnumuesschedperttidl(cellConfigReport.getMaxNumUesSchedPerTtiDl());
    cellConfigValues.set_maxnumuesschedperttiul(cellConfigReport.getMaxNumUesSchedPerTtiUl());
    cellConfigValues.set_dlfsschedenable(cellConfigReport.getDlfsSchedEnable());

    //output
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

    delete ecgi;
    cellConfigValues.clear_candscells(); //delete candscell inside
}
