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

#include "gRPCParam-CellConfigReportMsg.h"

gRPCParamCellConfigReportMsg::gRPCParamCellConfigReportMsg() {
    this->xRANConfigurationMsgType = CELL_CONFIGURATION;
}

gRPCParamCellConfigReportMsg::gRPCParamCellConfigReportMsg(std::string plmnId, std::string ecid) {
    this->xRANConfigurationMsgType = CELL_CONFIGURATION;
    this->ecgi = gRPCSubParamECGIMsg(plmnId, ecid);
}

gRPCParamCellConfigReportMsg::gRPCParamCellConfigReportMsg(gRPCSubParamECGIMsg ecgi) {
    this->xRANConfigurationMsgType = CELL_CONFIGURATION;
    this->ecgi = gRPCSubParamECGIMsg(ecgi.getPlmnId(), ecgi.getEcid());
}

gRPCParamCellConfigReportMsg::~gRPCParamCellConfigReportMsg() {}

gRPCSubParamECGIMsg
gRPCParamCellConfigReportMsg::getEcgi() {
    return ecgi;
}

void
gRPCParamCellConfigReportMsg::setEcgi(std::string plmnId, std::string ecid) {
    this->ecgi = gRPCSubParamECGIMsg(plmnId, ecid);
}

void
gRPCParamCellConfigReportMsg::setEcgi(gRPCSubParamECGIMsg ecgi) {
    this->ecgi = gRPCSubParamECGIMsg(ecgi.getPlmnId(), ecgi.getEcid());
}

std::string
gRPCParamCellConfigReportMsg::getPci() {
    return pci;
}

void
gRPCParamCellConfigReportMsg::setPci(std::string pci) {
    this->pci = pci;
}

std::vector<gRPCSubParamCandScellMsg>
gRPCParamCellConfigReportMsg::getCandScells() {
    return candScells;
}

void
gRPCParamCellConfigReportMsg::setCandScells(std::vector<gRPCSubParamCandScellMsg> candScells) {
    for (int index = 0; index < candScells.size(); index++) {
        this->candScells.push_back(candScells.at(index));
    }
}

gRPCSubParamCandScellMsg
gRPCParamCellConfigReportMsg::getCandScellWithIndex(int index) {
    if (this->candScells.empty()) {
        throw "Cand-Scells vector is not initialized or empty";
    } else if (this->candScells.size() <= index) {
        throw "Access out of Cand-Scells vector";
    }

    return candScells.at(index);
}

std::string
gRPCParamCellConfigReportMsg::getEarfcnDl() {
    return earfcnDl;
}

void
gRPCParamCellConfigReportMsg::setEarfcnDl(std::string earfcnDl) {
    this->earfcnDl = earfcnDl;
}

std::string
gRPCParamCellConfigReportMsg::getEarfcnUl() {
    return earfcnUl;
}

void
gRPCParamCellConfigReportMsg::setEarfcnUl(std::string earfcnUl) {
    this->earfcnUl = earfcnUl;
}

std::string
gRPCParamCellConfigReportMsg::getRbsPerTtiDl() {
    return rbsPerTtiDl;
}

void
gRPCParamCellConfigReportMsg::setRbsPerTtiDl(std::string rbsPerTtiDl) {
    this->rbsPerTtiDl = rbsPerTtiDl;
}

std::string
gRPCParamCellConfigReportMsg::getRbsPerTtiUl() {
    return rbsPerTtiUl;
}

void
gRPCParamCellConfigReportMsg::setRbsPerTtiUl(std::string rbsPerTtiUl) {
    this->rbsPerTtiUl = rbsPerTtiUl;
}

std::string
gRPCParamCellConfigReportMsg::getNumTxAntenna() {
    return numTxAntenna;
}

void
gRPCParamCellConfigReportMsg::setNumTxAntenna(std::string numTxAntenna) {
    this->numTxAntenna = numTxAntenna;
}

std::string
gRPCParamCellConfigReportMsg::getDuplexMode() {
    return duplexMode;
}

void
gRPCParamCellConfigReportMsg::setDuplexMode(std::string duplexMode) {
    this->duplexMode = duplexMode;
}

std::string
gRPCParamCellConfigReportMsg::getMaxNumConnectedUes() {
    return maxNumConnectedUes;
}

void
gRPCParamCellConfigReportMsg::setMaxNumConnectedUes(std::string maxNumConnectedUes) {
    this->maxNumConnectedUes = maxNumConnectedUes;
}

std::string
gRPCParamCellConfigReportMsg::getMaxNumConnectedBearers() {
    return maxNumConnectedBearers;
}

void
gRPCParamCellConfigReportMsg::setMaxNumConnectedBearers(std::string maxNumConnectedBearers) {
    this->maxNumConnectedBearers = maxNumConnectedBearers;
}

std::string
gRPCParamCellConfigReportMsg::getMaxNumUesSchedPerTtiDl() {
    return maxNumUesSchedPerTtiDl;
}

void
gRPCParamCellConfigReportMsg::setMaxNumUesSchedPerTtiDl(std::string maxNumUesSchedPerTtiDl) {
    this->maxNumUesSchedPerTtiDl = maxNumUesSchedPerTtiDl;
}

std::string
gRPCParamCellConfigReportMsg::getMaxNumUesSchedPerTtiUl() {
    return maxNumUesSchedPerTtiUl;
}

void
gRPCParamCellConfigReportMsg::setMaxNumUesSchedPerTtiUl(std::string maxNumUesSchedPerTtiUl) {
    this->maxNumUesSchedPerTtiUl = maxNumUesSchedPerTtiUl;
}

std::string
gRPCParamCellConfigReportMsg::getDlfsSchedEnable() {
    return dlfsSchedEnable;
}

void
gRPCParamCellConfigReportMsg::setDlfsSchedEnable(std::string dlfsSchedEnable) {
    this->dlfsSchedEnable = dlfsSchedEnable;
}

std::ostream&
operator<<(std::ostream& os, gRPCParamCellConfigReportMsg cellConfigReport) {

    std::cout << "ECGI: PLMN-ID - " << cellConfigReport.getEcgi().getPlmnId() << " ECID - " << cellConfigReport.getEcgi().getEcid() << std::endl;
    std::cout << "PCI: " << cellConfigReport.getPci() << std::endl;
    for (int index = 0; index < cellConfigReport.getCandScells().size(); index++) {
        std::cout << "Cand-Scell index #" << index << " - {PCI: " << cellConfigReport.getCandScells()[index].getPci() << ", earfcnDl: " << cellConfigReport.getCandScells()[index].getEarfcnDl() << "}" << std::endl;
    }
    std::cout << "earfcnDl: " << cellConfigReport.getEarfcnDl() << std::endl;
    std::cout << "earfcnUl: " << cellConfigReport.getEarfcnUl() << std::endl;
    std::cout << "rbsPerTtiDl: " << cellConfigReport.getRbsPerTtiDl() << std::endl;
    std::cout << "rbsPerTtiUl: " << cellConfigReport.getRbsPerTtiUl() << std::endl;
    std::cout << "numTxAntenna: " << cellConfigReport.getNumTxAntenna() << std::endl;
    std::cout << "duplexMode: " << cellConfigReport.getDuplexMode() << std::endl;
    std::cout << "maxNumConnectedUes: " << cellConfigReport.getMaxNumConnectedUes() << std::endl;
    std::cout << "maxNumConnectedBearers: " << cellConfigReport.getMaxNumConnectedBearers() << std::endl;
    std::cout << "maxNumUesSchedPerTtiDl: " << cellConfigReport.getMaxNumUesSchedPerTtiDl() << std::endl;
    std::cout << "maxNumUesSchedPerTtiUl: " << cellConfigReport.getMaxNumUesSchedPerTtiUl() << std::endl;
    std::cout << "dlfsSchedEnable: " << cellConfigReport.getDlfsSchedEnable() << std::endl;

    return os;
}