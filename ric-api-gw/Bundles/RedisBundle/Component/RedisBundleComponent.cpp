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

#include "RedisBundleComponent.h"

void 
RedisBundleComponent::setLogService(const log_service_t* logSrv) {
    //for logging
    std::cout << "RedisBundleComponent - setLogService" << std::endl;
    this->logSrv = logSrv;
}

void
RedisBundleComponent::notifyEvent(std::string srcBundle, std::string dstBundle, std::map<std::string, std::map<std::string, std::string>> statements) {
    std::string notifyResult = "SRC: " + srcBundle + " DST: " + dstBundle;
    APIGWLogDEBUG(logSrv, notifyResult);
    updateCellConfigReport(statements);
}

void
RedisBundleComponent::registerBundle() {
    std::cout << "RedisBundleComponent - registerBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Register " << REDIS_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    
    if (gwCoreComponent) {
        gwCoreComponent->registerBundle(REDIS_BUNDLE_KEY, this);
        logMsg.flush();
        logMsg << "Finished to register " << REDIS_BUNDLE_KEY << " Bundle";

        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
RedisBundleComponent::unregisterBundle() {
    std::cout << "RedisBundleComponent - unregisterBundle" << std::endl;
    std::stringstream logMsg;
    logMsg << "Unregister " << REDIS_BUNDLE_KEY << " Bundle";
    APIGWLogINFO(this->logSrv, logMsg.str().c_str());

    if (gwCoreComponent) {
        gwCoreComponent->unregisterBundle(REDIS_BUNDLE_KEY);
        logMsg.flush();
        logMsg << "Finished to register " << REDIS_BUNDLE_KEY << " Bundle";
        
        APIGWLogINFO(this->logSrv, logMsg.str().c_str());
    } else {
        APIGWLogERROR(this->logSrv, logMsg.str().c_str());
    }
}

void
RedisBundleComponent::init() {
    std::cout << "RedisBundleComponent - init" << std::endl;
}

void
RedisBundleComponent::start() {
    std::cout << "RedisBundleComponent - start" << std::endl;
    this->registerBundle();
}

void
RedisBundleComponent::stop() {
    std::cout << "RedisBundleComponent - stop" << std::endl;
    this->unregisterBundle();
}

void
RedisBundleComponent::deinit() {
    std::cout << "RedisBundleComponent - deinit" << std::endl;
}

 void
RedisBundleComponent::setGWCoreComponent(AbstractGWCoreComponent* gwcore) {
    this->gwCoreComponent = gwcore;
}

AbstractGWCoreComponent*
RedisBundleComponent::getGWCoreComponent() {
    return gwCoreComponent;
}

void
RedisBundleComponent::updateCellConfigReport(std::map<std::string, std::map<std::string, std::string>> statements) {
    
    struct timeval timeout = {REDIS_TIMEOUT_SEC, REDIS_TIMOUET_USEC};
    redisContext* context = redisConnectWithTimeout(REDIS_DB_IP, REDIS_DB_PORT, timeout);

    if (context == NULL && context->err) {
        if (context) {
            std::stringstream errorMsg;
            errorMsg << "Connection Error: " << context->errstr;
            APIGWLogERROR(logSrv, errorMsg.str());
        } else {
            APIGWLogERROR(logSrv, "Connection Error: Cannot allocate redis context");
        }
    }

    // push ECGI
    std::stringstream tmpEcgiKey;
    tmpEcgiKey << DB_ECGI_KEY << ":" << statements.at(DB_ECGI_KEY).at(DB_PLMNID_KEY) << "+" << statements.at(DB_ECGI_KEY).at(DB_ECID_KEY);
    std::stringstream queryEcgi;
    queryEcgi << "hmset " << tmpEcgiKey.str() << " " << DB_PLMNID_KEY << " " << statements.at(DB_ECGI_KEY).at(DB_PLMNID_KEY) << " " << DB_ECGI_KEY << " " << statements.at(DB_ECGI_KEY).at(DB_ECID_KEY);
    redisReply* reply = (redisReply*)redisCommand(context, queryEcgi.str().c_str());
    freeReplyObject(reply);
    queryEcgi.str("");
    queryEcgi << "sadd " << DB_ECGI_LIST << " " << tmpEcgiKey.str();
    reply = (redisReply*)redisCommand(context, queryEcgi.str().c_str());
    freeReplyObject(reply);
    queryEcgi.str("");

    // push Cand-Scells
    std::stringstream tmpCandScellsKey;
    tmpCandScellsKey << DB_CAND_SCELL_KEY << ":" << tmpEcgiKey.str();
    std::stringstream queryCandScells;
    for (std::map<std::string, std::string>::iterator it = statements[DB_CAND_SCELLS_KEY].begin(); it != statements[DB_CAND_SCELLS_KEY].end(); ++it) {
        queryCandScells.str("");
        std::string tmpCandScellKey = tmpCandScellsKey.str() + ":" + it->first;
        queryCandScells << "sadd " << DB_CSCELLS_LIST << " " << tmpCandScellsKey.str();
        reply = (redisReply*)redisCommand(context, queryCandScells.str().c_str());
        freeReplyObject(reply);
        
        queryCandScells.str("");
        queryCandScells << "sadd " << tmpCandScellsKey.str() << " " << tmpCandScellKey;
        reply = (redisReply*)redisCommand(context, queryCandScells.str().c_str());
        freeReplyObject(reply);

        std::stringstream tmpCellKey;
        tmpCellKey << DB_CAND_SCELL_KEY << ":" << it->first;
        queryCandScells.str("");
        queryCandScells << "hmset " << tmpCandScellKey << " " << DB_PCI_KEY << " " << statements.at(it->second).at(DB_PCI_KEY) << " " << DB_EARFCN_DL << " " << statements.at(it->second).at(DB_EARFCN_DL);
        reply = (redisReply*)redisCommand(context, queryCandScells.str().c_str());
        freeReplyObject(reply);
    }

    // push eNB
    std::stringstream tmpENBKey;
    tmpENBKey << DB_ENB_KEY << ":" << tmpEcgiKey.str();
    std::stringstream queryENB;
    queryENB << "hmset " << tmpENBKey.str() << " " << DB_ECGI_KEY << " " << tmpEcgiKey.str() << " " << DB_PCI_KEY << " " << statements.at(DB_ENB_KEY).at(DB_PCI_KEY)
        << " " << DB_CAND_SCELLS_KEY << " " << tmpCandScellsKey.str() << " " << DB_EARFCN_DL << " " << statements.at(DB_ENB_KEY).at(DB_EARFCN_DL)
        << " " << DB_EARFCN_UL << " " << statements.at(DB_ENB_KEY).at(DB_EARFCN_UL) << " " << DB_RBS_PER_TTI_DL
        << " " << statements.at(DB_ENB_KEY).at(DB_RBS_PER_TTI_DL) << " " << DB_RBS_PER_TTI_UL << " " << statements.at(DB_ENB_KEY).at(DB_RBS_PER_TTI_UL)
        << " " << DB_NUM_TX_ANTENNAS << " " << statements.at(DB_ENB_KEY).at(DB_NUM_TX_ANTENNAS) << " " << DB_DUPLEX_MODE
        << " " << statements.at(DB_ENB_KEY).at(DB_DUPLEX_MODE) << " " << DB_MAX_NUM_CONNECTED_UES << " " << statements.at(DB_ENB_KEY).at(DB_MAX_NUM_CONNECTED_UES)
        << " " << DB_MAX_NUM_CONNECTED_BEARERS << " " << statements.at(DB_ENB_KEY).at(DB_MAX_NUM_CONNECTED_BEARERS) << " " << DB_MAX_NUM_UES_SCHED_PER_TTI_DL
        << " " << statements.at(DB_ENB_KEY).at(DB_MAX_NUM_UES_SCHED_PER_TTI_DL) << " " << DB_MAX_NUM_UES_SCHED_PER_TTI_UL
        << " " << statements.at(DB_ENB_KEY).at(DB_MAX_NUM_UES_SCHED_PER_TTI_UL) << " " << DB_DFLS_SCHED_ENABLE 
        << " " << statements.at(DB_ENB_KEY).at(DB_DFLS_SCHED_ENABLE);
    reply = (redisReply*)redisCommand(context, queryENB.str().c_str());
    freeReplyObject(reply);
    queryENB.str("");
    queryENB << "sadd " << DB_ENB_LIST << " " << tmpENBKey.str();
    reply = (redisReply*)redisCommand(context, queryENB.str().c_str());
    freeReplyObject(reply);
}