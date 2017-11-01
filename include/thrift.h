#ifndef _THRIFT_H_
#define _THRIFT_H_

#include "Dial.h"
#include "dnsrpc_types.h"

using namespace  ::rpc::yamutech::com;


class DialHandler : virtual public DialIf {

 public:

  DialHandler(){}
  ~DialHandler(){}
  
  RetCode::type systemCommand(const SysCommand::type cmdType);
  //RetCode::type isPrimary(const bool isPrimary);
  RetCode::type addHealthGroup(const HealthGroupInfo& health, const std::string& policyName);
  RetCode::type delHealthGroup(const HealthGroupInfo& health, const std::string& policyName);
  //RetCode::type delHealthGroup(const HealthGroupInfo& health);
  RetCode::type addHealthRecord(const HealthGroupInfo& health, const DialRecord& rec);
  RetCode::type modHealthRecord(const HealthGroupInfo& health, const DialRecord& rec);
  RetCode::type delHealthRecord(const HealthGroupInfo& health, const DialRecord& rec);
  RetCode::type addHealthPolicy(const HealthPolicyInfo& policy);
  RetCode::type modHealthPolicy(const HealthPolicyInfo& policy);
  RetCode::type delHealthPolicy(const HealthPolicyInfo& policy);
  RetCode::type dialServerConfig(const DialServerType::type typ, const bool allowed);
  RetCode::type addDialServer(const IpAddr& ip, const DialServerType::type typ);
  RetCode::type delDialServer(const IpAddr& ip, const DialServerType::type typ);
  RetCode::type addNginxGroup(const std::string& groupName, const std::string& policyName);
  RetCode::type delNginxGroup(const std::string& groupName, const std::string& policyName);
  //RetCode::type delNginxGroup(const std::string& groupName);
  RetCode::type addNginxServer(const std::string& groupName, const DialNginxServer& server);
  RetCode::type modNginxServer(const std::string& groupName, const DialNginxServer& server);
  RetCode::type delNginxServer(const std::string& groupName, const DialNginxServer& server);
  void heartBeat(HeartBeatState& _return);
  RetCode::type setServerState(const bool enable);

};

void thrift_client_init();

void thrift_init();

#endif
