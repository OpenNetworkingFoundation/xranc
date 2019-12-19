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

#ifndef _GRPCPARAM_PROCEDURALMSG_
#define _GRPCPARAM_PROCEDURALMSG_

#include <iostream>

#include "gRPCParam-Msg.h"

typedef enum {
    UNKNOWN_PROCEDURAL_MESSAGE_TYPE=0,
    ADMISSION_CONTROL,
    HANDOVER_MANAGEMENT,
    BEARER_MANAGEMENT
} XRANProceduralMsgType;

class gRPCParamProceduralMsg : public gRPCParamMsg {

    public:
        gRPCParamProceduralMsg();
        ~gRPCParamProceduralMsg();
        XRANProceduralMsgType getXRANProceduralMsgType();
        void setXRANProceduralMsgType(XRANProceduralMsgType xRANProceduralMsgType);

    private:

    protected:
        XRANProceduralMsgType xRANProceduralMsgType;
};

std::string XRANProceduralMsgTypeAsString(XRANProceduralMsgType xRANProceduralMsgType);
std::ostream& operator<<(std::ostream& os, XRANProceduralMsgType xRANProceduralMsgType);

#endif /* _GRPCPARAM_PROCEDURALMSG_ */