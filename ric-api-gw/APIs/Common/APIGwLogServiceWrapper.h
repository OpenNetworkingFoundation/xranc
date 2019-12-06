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

#include <iostream>

#include <log_service.h>
#include <log_helper.h>

inline void APIGWLogINFO(const log_service_t* logSrv, std::string msg ) {
    if (logSrv) {
        logSrv->log(logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) msg.c_str());
    } else {
        std::cout << "[LOGSERVICE IS NOT SET - INFO]: " << msg << std::endl;
    }
}
inline void APIGWLogERROR(const log_service_t* logSrv, std::string msg ) {
    if (logSrv) {
        logSrv->log(logSrv->logger, OSGI_LOGSERVICE_INFO, (char *) msg.c_str());
    } else {
        std::cout << "[LOGSERVICE IS NOT SET - INFO]: " << msg << std::endl;
    }
}

inline void APIGWLogDEBUG(const log_service_t* logSrv, std::string msg ) {
    if (logSrv) {
        logSrv->log(logSrv->logger, OSGI_LOGSERVICE_DEBUG, (char *) msg.c_str());
    } else {
        std::cout << "[LOGSERVICE IS NOT SET - INFO]: " << msg << std::endl;
    }
}

inline void APIGWLogWARN(const log_service_t* logSrv, std::string msg ) {
    if (logSrv) {
        logSrv->log(logSrv->logger, OSGI_LOGSERVICE_WARNING, (char *) msg.c_str());
    } else {
        std::cout << "[LOGSERVICE IS NOT SET - INFO]: " << msg << std::endl;
    }
}

#endif /* _APIGW_LOG_SERVICE_WRAPPER_H_ */