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

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <config.h>
#include <enbsim.h>
#include "logger.h"

using namespace std;

// GLobal logging level
#define LOG_LEVEL spdlog::level::debug

int main(int argc, char *argv[]) {
    Config* config = Config::Instance();
    config->parse("enbsim.json");

    logger_init(LOG_LEVEL);
    log_info("Welcome to enbsim");

    //Config* config = Config::Instance("xran-cfg.json");
    cout << *config;
    enbsim_main(argc, argv, *config);
}
