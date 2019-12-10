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

#ifndef _APIGW_LOG_SERVICE_WRAPPER_H_
#define _APIGW_LOG_SERVICE_WRAPPER_H_

#define API_GW_LOG_LEVEL log_level_t::OSGI_LOGSERVICE_DEBUG //log_level_t::OSGI_FRAMEWORK_LOG_ERROR, OSGI_FRAMEWORK_LOG_WARNING, OSGI_FRAMEWORK_LOG_INFO, OSGI_FRAMEWORK_LOG_DEBUG

#include <iostream>

#include <log_service.h>
#include <log_helper.h>

inline void APIGWLogINFO(const log_service_t* logSrv, std::string msg ) {

    if (API_GW_LOG_LEVEL >= log_level_t::OSGI_LOGSERVICE_INFO) {
        if (logSrv) {
            msg = "\033[0;32m[INFO] \033[0;m" + msg;
            logSrv->log(logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) msg.c_str());
        } else {
            std::cout << "[No Logservice - \033[0;32mINFO\033[0;m]: " << msg << std::endl;
        }
    }
}
inline void APIGWLogERROR(const log_service_t* logSrv, std::string msg ) {

    if (API_GW_LOG_LEVEL >= log_level_t::OSGI_LOGSERVICE_ERROR) {
        if (logSrv) {
            msg = "\033[0;31m[ERROR] \033[0;m" + msg;
            logSrv->log(logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) msg.c_str());
        } else {
            std::cout << "[No Logservice - \033[0;31mERROR\033[0;m]: " << msg << std::endl;
        }
    }
}

inline void APIGWLogDEBUG(const log_service_t* logSrv, std::string msg ) {

    if (API_GW_LOG_LEVEL >= log_level_t::OSGI_LOGSERVICE_DEBUG) {
        if (logSrv) {
            msg = "\033[0;36m[DEBUG] \033[0;m" + msg;
            logSrv->log(logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) msg.c_str());
        } else {
            std::cout << "[No Logservice - \033[0;35mDEBUG\033[0;m]: " << msg << std::endl;
        }
    }
}

inline void APIGWLogWARN(const log_service_t* logSrv, std::string msg ) {

    if (API_GW_LOG_LEVEL >= log_level_t::OSGI_LOGSERVICE_WARNING) {
        if (logSrv) {
            msg = "\033[0;33m[WARN] \033[0;m" + msg;
            logSrv->log(logSrv->logger, OSGI_LOGSERVICE_WARNING, (char *) msg.c_str());
        } else {
            std::cout << "[No Logservice - \033[0;33mWARNNING\033[0;m]: " << msg << std::endl;
        }
    }
}

#endif /* _APIGW_LOG_SERVICE_WRAPPER_H_ */