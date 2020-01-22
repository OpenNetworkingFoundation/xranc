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

#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <map>

// Hardcoded: Must be removed!
#define GRPC_SB_CELLCONFIG_PORT "50002"
#define GRPC_SB_UEADMSTAT_PORT "50003"
#define GRPC_SB_UECONTEXTUPDATE_PORT "50004"

using namespace std;

struct Cell {
    string plmn_id;
    string eci;
    string ip_addr;
};

class Config {
    public:
        map<string, Cell> active_cells;
        unsigned int l2_meas_report_interval_ms;
        unsigned int rx_signal_meas_report_interval_ms;
        unsigned int xranc_cellconfigrequest_interval_seconds;
        string xranc_bind_ip;
        string xranc_port;
        bool admission_success;
        bool bearer_success;
        unsigned int no_meas_link_removal_ms;
        unsigned int idle_ue_removal_ms;
        unsigned int nb_response_timeout_ms;
        string api_gw_ip_addr;
        unsigned int api_gw_sbbundle_port;

        static Config* Instance();
        void parse(string config_file);
        void get_plmn_id(char *ip, uint8_t *plmn_id);
        void get_eci(char *ip, uint8_t *eci);
        friend ostream & operator << (ostream &out, const Config &c);

    private:
        Config() {};
        Config(Config const&) {};
        static Config* pInstance;
};

void get_plmn_id(char *ip, uint8_t *plmn_id);

#endif
