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

#ifndef _GRPCSUBPARAM_MSG_
#define _GRPCSUBPARAM_MSG_

#include <iostream>

typedef enum {
    UNKNOWN_XRAN_PARAM_TYPE=0,
    XRAN_PARAM_ECGI,
    XRAN_PARAM_CAND_SCELL
} XRANParamType;

class gRPCSubParamMsg {
    public:
        gRPCSubParamMsg();
        ~gRPCSubParamMsg();
        virtual std::string getGRPCSubParamString() = 0;
        XRANParamType getXRANParamType();
        void setXRANParamType(XRANParamType xRANParamType);
    private:

    protected:
        XRANParamType xRANParamType;
};

std::string XRANParamTypeAsString(XRANParamType xRANParamType);
std::ostream& operator<<(std::ostream& os, XRANParamType xRANParamType);

#endif /* _GRPCSUBPARAM_MSG_ */