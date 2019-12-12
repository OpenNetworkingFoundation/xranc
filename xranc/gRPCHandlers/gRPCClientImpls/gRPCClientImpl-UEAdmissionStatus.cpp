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

#include "gRPCClientImpl-UEAdmissionStatus.h"

int 
gRPCClientImplUEAdmissionStatus::UpdateUEAdmissionStatus(gRPCParamUEAdmissionStatusMsg ueAdmissionStatusMsg) {
    gMsgECGI* ecgi = new gMsgECGI();
    ecgi->set_plmnid(ueAdmissionStatusMsg.getEcgi().getPlmnId());
    ecgi->set_ecid(ueAdmissionStatusMsg.getEcgi().getEcid());

    gMSGUEAdmissionStatusValues ueAdmissionStatusValues;
    ueAdmissionStatusMsg.setCrnti(ueAdmissionStatusMsg.getCrnti());
    ueAdmissionStatusMsg.setAdmissionEstStatus(ueAdmissionStatusMsg.getAdmissionEstStatus());

    gMsgResults results;
    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<gMsgResults>> rpc(stub_->PrepareAsyncUpdateUEAdmissionStatus(&context, ueAdmissionStatusValues, &cq));

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