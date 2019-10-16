#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <config.h>

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
        active_cells.push_back(cell);
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
    for(auto cell : c.active_cells) {
        cout << endl;
        cout << "   ip_addr :" << cell.ip_addr << endl;
        cout << "   plmn_id :" << cell.plmn_id << endl;
        cout << "   eci :" << cell.eci << endl;
    }
    return out;
}
