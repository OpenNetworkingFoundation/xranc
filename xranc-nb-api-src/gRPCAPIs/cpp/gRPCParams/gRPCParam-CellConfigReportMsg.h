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

#ifndef _GRPCPARAM_CELLCONFIGREPORTMSG_
#define _GRPCPARAM_CELLCONFIGREPORTMSG_

#include <iostream>
#include <vector>

#include "gRPCParam-ConfigurationMsg.h"
#include "gRPCSubParam-ECGIMsg.h"
#include "gRPCSubParam-CandScellMsg.h"

class gRPCParamCellConfigReportMsg : public gRPCParamConfigurationMsg {

    public:
        gRPCParamCellConfigReportMsg();
        gRPCParamCellConfigReportMsg(std::string plmnId, std::string ecid);
        gRPCParamCellConfigReportMsg(gRPCSubParamECGIMsg ecgi);
        ~gRPCParamCellConfigReportMsg();
        gRPCSubParamECGIMsg getEcgi();
        void setEcgi(std::string plmnId, std::string ecid);
        void setEcgi(gRPCSubParamECGIMsg ecgi);
        std::string getPci();
        void setPci(std::string pci);
        std::vector<gRPCSubParamCandScellMsg> getCandScells();
        void setCandScells(std::vector<gRPCSubParamCandScellMsg> candScells);
        gRPCSubParamCandScellMsg getCandScellWithIndex(int index);
        std::string getEarfcnDl();
        void setEarfcnDl(std::string earfcnDl);
        std::string getEarfcnUl();
        void setEarfcnUl(std::string earfcnUl);
        std::string getRbsPerTtiDl();
        void setRbsPerTtiDl(std::string rbsPerTtiDl);
        std::string getRbsPerTtiUl();
        void setRbsPerTtiUl(std::string rbsPerTtiUl);
        std::string getNumTxAntenna();
        void setNumTxAntenna(std::string numTxAntenna);
        std::string getDuplexMode();
        void setDuplexMode(std::string duplexMode);
        std::string getMaxNumConnectedUes();
        void setMaxNumConnectedUes(std::string maxNumConnectedUes);
        std::string getMaxNumConnectedBearers();
        void setMaxNumConnectedBearers(std::string maxNumConnectedBearers);
        std::string getMaxNumUesSchedPerTtiDl();
        void setMaxNumUesSchedPerTtiDl(std::string maxNumUesSchedPerTtiDl);
        std::string getMaxNumUesSchedPerTtiUl();
        void setMaxNumUesSchedPerTtiUl(std::string maxNumUesSchedPerTtiUl);
        std::string getDlfsSchedEnable();
        void setDlfsSchedEnable(std::string dlfsSchedEnable);
        
    private:
        gRPCSubParamECGIMsg ecgi;
        std::string pci;
        std::vector<gRPCSubParamCandScellMsg> candScells;
        std::string earfcnDl;
        std::string earfcnUl;
        std::string rbsPerTtiDl;
        std::string rbsPerTtiUl;
        std::string numTxAntenna;
        std::string duplexMode;
        std::string maxNumConnectedUes;
        std::string maxNumConnectedBearers;
        std::string maxNumUesSchedPerTtiDl;
        std::string maxNumUesSchedPerTtiUl;
        std::string dlfsSchedEnable;

    protected:
    
};

std::ostream& operator<<(std::ostream& os, gRPCParamCellConfigReportMsg cellConfigReport);

#endif /* _GRPCPARAM_CELLCONFIGREPORTMSG_ */