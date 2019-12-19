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

#ifndef _GRPCCLIENT_UECONTEXTUPDATE_H_
#define _GRPCCLIENT_UECONTEXTUPDATE_H_

#include "gRPCClient.h"
#include "../gRPCParams/gRPCParam-UEContextUpdateMsg.h"
#include "../gRPCPB/gRPC-UEContextUpdate.grpc.pb.h"

class gRPCClientUEContextUpdate : public gRPCClient {

    public:
        gRPCClientUEContextUpdate();
        ~gRPCClientUEContextUpdate();
        virtual int UpdateUEContext(gRPCParamUEContextUpdateMsg ueContextUpdateMsg) = 0;

    private:

    protected:
};

#endif /* _GRPCCLIENT_UECONTEXTUPDATE_H_ */