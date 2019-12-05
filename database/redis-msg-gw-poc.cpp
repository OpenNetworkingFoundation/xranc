#include <iostream>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <hiredis.h>
#include <memory>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>


#include <gRPCAPIs/cpp/gRPCPB/gRPC-CellConfigReport.grpc.pb.h>
#include <gRPCAPIs/cpp/gRPCParams/gRPCParam-CellConfigReportMsg.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using gRPCCellConfigReport::gRPCCellConfigReportUpdater;
using gRPCCellConfigReport::gMsgECGI;
using gRPCCellConfigReport::gMsgCandScell;
using gRPCCellConfigReport::gMsgCellConfigValues;
using gRPCCellConfigReport::gMsgResults;

class gRPCCellConfigReportServerImpl final : public gRPCCellConfigReportUpdater::Service {
    Status UpdateCellConfig(ServerContext* context, const gMsgCellConfigValues* request, gMsgResults* reply) override {
        std::cout << "PLMNID: " << request->ecgi().plmnid() << std::endl;
        std::cout << "ECID: " << request->ecgi().ecid() << std::endl;
        std::cout << "PCI: " << request->pci() << std::endl;
        for (int index = 0; index < request->candscells_size(); index++) {
            std::cout << "Cand-Scells (" << index << ")" << std::endl;
            std::cout << "   * PCI: " << request->candscells(index).pci() << std::endl;
            std::cout << "   * EARFCN DL: " << request->candscells(index).earfcndl() << std::endl;
        }
        std::cout << "EARFCN DL: " << request->earfcndl() << std::endl;
        std::cout << "EARFCN UL: " << request->earfcnul() << std::endl;
        std::cout << "RBS Per TTI DL: " << request->rbsperttidl() << std::endl;
        std::cout << "RBS Per TTI UL: " << request->rbsperttiul() << std::endl;
        std::cout << "Num TX Antennas: " << request->numtxantenna() << std::endl;
        std::cout << "Duplex Mode: " << request->duplexmode() << std::endl; // 0: fdd, 1: tdd
        std::cout << "Max Num Connected UEs: " << request->maxnumconnectedues() << std::endl;
        std::cout << "Max Num Connected Bearers: " << request->maxnumconnectedbearers() << std::endl;
        std::cout << "Max Num UEs Sched Per TTI DL: " << request->maxnumuesschedperttidl() << std::endl;
        std::cout << "Max Num UEs Sched Per TTI UL: " << request->maxnumuesschedperttiul() << std::endl;
        std::cout << "DLFS Sched Enable: " << request->dlfsschedenable() << std::endl; // 0: false, 255: true

        std::string redisIp = "172.17.0.2";
        int redisPort = 6379;
        struct timeval timeout = { 1, 500000 };

        redisContext* c = redisConnectWithTimeout(redisIp.c_str(), redisPort, timeout);

        if (c == NULL && c->err) {
            if (c) {
                std::cout << "Connection error: " << c->errstr << std::endl;
                redisFree(c);
            } else {
                std::cout << "Connection error: cannot allocate redis context" << std::endl;
            }
            return Status::OK;
        }

        std::string redisQuery = "PING";

        //ping-pong first
        redisReply* r = (redisReply*)redisCommand(c,redisQuery.c_str());
        std::cout << r->str << std::endl;
        freeReplyObject(r);

        //PUSH ECGI Info
        std::string tmpECGIKey = "ECGI:" + request->ecgi().plmnid() + "+" + request->ecgi().ecid();
        redisQuery = "hmset " + tmpECGIKey + " PLMN-ID " + request->ecgi().plmnid() + " ECID " + request->ecgi().ecid();
        r = (redisReply*)redisCommand(c,redisQuery.c_str());
        freeReplyObject(r);

        //PUSH ECGI into ECGIs list for update if key does not exist
        redisQuery = "sadd LIST-ECGI " + tmpECGIKey;
        r = (redisReply*)redisCommand(c,redisQuery.c_str());
        freeReplyObject(r);

        //PUSH Cand-Scell into Cand-Scells list
        std::string tmpCandScellKey = "CAND-SCELL:" + tmpECGIKey;

        for (int index = 0; index < request->candscells_size(); index++) {
            redisQuery = "hmset " + tmpCandScellKey + ":" + std::to_string(index) + " PCI " + request->candscells(index).pci() + " EARFCN-DL " + request->candscells(index).earfcndl();
            r = (redisReply*)redisCommand(c,redisQuery.c_str());
            freeReplyObject(r);
            redisQuery = "sadd " + tmpCandScellKey + " " + tmpCandScellKey + ":" + std::to_string(index);
            r = (redisReply*)redisCommand(c,redisQuery.c_str());
            freeReplyObject(r);
        }

        //PUSH eNB Info
        std::string tmpEnBKey = "eNB:" + tmpECGIKey;
        redisQuery = "hmset " + tmpEnBKey + " ECGI " + tmpECGIKey + " PCI " + request->pci() + " CAND-SCELLS " + tmpCandScellKey + 
            " EARFCN-DL " + request->earfcndl() + " EARFCN-UL " + request->earfcnul() + " RBS-PER-TTI-DL " + request->rbsperttidl() + 
            " RBS-PER-TTI-UL " + request->rbsperttiul() + " NUM-TX-ANTENNAS " + request->numtxantenna() + " DUPLEX-MODE " + request->duplexmode() + 
            " MAX-NUM-CONNECTED-UES " + request->maxnumconnectedues() + " MAX-NUM-CONNECTED-BEARERS " + request->maxnumconnectedbearers() + 
            " MAX-NUM-UES-SCHED-PER-TTI-DL " + request->maxnumuesschedperttidl() + " MAX-NUM-UES-SCHED-PER-TTI-UL " + request->maxnumuesschedperttiul() + 
            " DLFS-SCHED-ENABLE " + request->dlfsschedenable();
        r = (redisReply*)redisCommand(c,redisQuery.c_str());
        freeReplyObject(r);

        //PUSH eNB into eNBs list
        redisQuery = "sadd LIST-eNB " + tmpEnBKey;
        r = (redisReply*)redisCommand(c,redisQuery.c_str());
        freeReplyObject(r);

        redisFree(c);

        return Status::OK;
    }
};

int main() {
    std::string server_address("10.0.0.11:50002");
    gRPCCellConfigReportServerImpl service;
    ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return 0;
}