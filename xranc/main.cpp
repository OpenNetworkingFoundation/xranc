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

#include "logger.h"

#include <config.h>
#include <server.h>

int main(int argc, char *argv[]) {
    Config* config = Config::Instance();
    config->parse("xran-cfg.json");

    logger_init();
    log_info("Welcome to XRANC");

    log_debug("XRANC config: {}", *config);
    runServer(*config);
}
