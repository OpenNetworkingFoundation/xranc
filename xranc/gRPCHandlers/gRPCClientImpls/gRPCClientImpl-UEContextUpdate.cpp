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

#include "gRPCClientImpl-UEContextUpdate.h"

int
gRPCClientImplUEContextUpdate::UpdateUEContext(gRPCParamUEContextUpdateMsg ueContextUpdateMsg) {
    gMsgECGI* ecgi = new gMsgECGI();
    ecgi->set_plmnid(ueContextUpdateMsg.getEcgi().getPlmnId());
    ecgi->set_ecid(ueContextUpdateMsg.getEcgi().getEcid());

    gMsgUEContextValues ueContextValues;
    ueContextValues.set_crnti(ueContextUpdateMsg.getCrnti());
    ueContextValues.set_allocated_ecgi(ecgi);
    ueContextValues.set_mmeues1apid(ueContextUpdateMsg.getMmeUeS1apId());
    ueContextValues.set_enbues1apid(ueContextUpdateMsg.getEnbUeS1apId());
    ueContextValues.set_imsi(ueContextUpdateMsg.getImsi());

    gMsgResults results;
    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<gMsgResults>> rpc(stub_->PrepareAsyncUpdateUEContext(&context,
    ueContextValues, &cq));

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
}
