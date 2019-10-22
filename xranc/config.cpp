#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <config.h>
#include <string.h>

Config* Config::pInstance = NULL;

Config* Config::Instance() {
    if (!pInstance)
        pInstance = new Config;

    return pInstance;
}

void Config::parse(string config_file) {
    Json::Reader reader;
    Json::Value obj;

    ifstream ifs(config_file);
    reader.parse(ifs, obj);

    for (auto itr : obj["active_cells"]) {
        Cell cell;
        cell.plmn_id = itr["plmn_id"].asString();
        cell.eci = itr["eci"].asString();
        cell.ip_addr = itr["ip_addr"].asString();
        active_cells[cell.ip_addr] = cell;
    }

    l2_meas_report_interval_ms = obj["l2_meas_report_interval_ms"].asInt();
    rx_signal_meas_report_interval_ms = obj["rx_signal_meas_report_interval_ms"].asInt();
    xranc_cellconfigrequest_interval_seconds = obj["xranc_cellconfigrequest_interval_seconds"].asInt();
    xranc_bind_ip = obj["xranc_bind_ip"].asString();
    xranc_port = obj["xranc_port"].asString();
    admission_success = obj["admission_success"].asBool();
    bearer_success = obj["bearer_success"].asBool();
    no_meas_link_removal_ms = obj["no_meas_link_removal_ms"].asInt();
    idle_ue_removal_ms = obj["idle_ue_removal_ms"].asInt();
    nb_response_timeout_ms = obj["nb_response_timeout_ms"].asInt();
}

ostream & operator << (ostream &out, const Config &c) {
    cout << "l2_meas_report_interval_ms: " << c.l2_meas_report_interval_ms << endl;
    cout << "rx_signal_meas_report_interval_ms: " << c.rx_signal_meas_report_interval_ms << endl;
    cout << "xranc_cellconfigrequest_interval_seconds: " << c.xranc_cellconfigrequest_interval_seconds << endl;
    cout << "xranc_bind_ip: " << c.xranc_bind_ip << endl;
    cout << "xranc_port: " << c.xranc_port << endl;
    cout << "admission_success: " << c.admission_success << endl;
    cout << "bearer_success: " << c.bearer_success << endl;
    cout << "no_meas_link_removal_ms: " << c.no_meas_link_removal_ms << endl;
    cout << "idle_ue_removal_ms: " << c.idle_ue_removal_ms << endl;
    cout << "nb_response_timeout_ms: " << c.nb_response_timeout_ms << endl;

    for(auto const& x : c.active_cells) {
        Cell c = x.second;
        cout << endl;
        cout << "   ip_addr :" << c.ip_addr << endl;
        cout << "   plmn_id :" << c.plmn_id << endl;
        cout << "   eci :" << c.eci << endl;
    }

    return out;
}

static unsigned char* hexstr_to_char(const char* hexstr, uint8_t *chrs)
{
    size_t len = strlen(hexstr);
/*
    IF_ASSERT(len % 2 != 0)
        return NULL;
*/
    size_t final_len = len / 2;
    for (size_t i=0, j=0; j<final_len; i+=2, j++)
        chrs[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i+1] % 32 + 9) % 25;
    chrs[final_len] = '\0';
    return chrs;
}

void Config::get_plmn_id(char *ip, uint8_t *plmn_id) {
    struct Cell cell;
    Config* config = Config::Instance();

    cell = config->active_cells[ip];
    hexstr_to_char(cell.plmn_id.c_str(), plmn_id);
}

void Config::get_eci(char *ip, uint8_t *eci) {
    struct Cell cell;
    Config* config = Config::Instance();

    cell = config->active_cells[ip];
    hexstr_to_char(cell.eci.c_str(), eci);
}
