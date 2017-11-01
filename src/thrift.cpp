#include "Dial.h"
#include "Agent.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/protocol/TProtocol.h"
#include "thrift/server/TSimpleServer.h"
#include "thrift/transport/TServerSocket.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/transport/TSocket.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <arpa/nameser.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/resource.h>
#include <signal.h>
#include "thrift.h"
#include "config.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::rpc::yamutech::com;

boost::shared_ptr<TTransport> transport_client;
boost::shared_ptr<TProtocol> protocol_client;


void thrift_init()
{
	extern dial_cfg_t g_cfg;
	int port = g_cfg.dial_port;

	shared_ptr<DialHandler> handler(new DialHandler());
	shared_ptr<TProcessor> processor(new DialProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	
	server.serve();
}

void thrift_client_init()
{
	extern dial_cfg_t g_cfg;
	char* ip = g_cfg.agent_ip;
	int port = g_cfg.agent_port;

	boost::shared_ptr<TSocket> tsocket(new TSocket(ip, port));  
	boost::shared_ptr<TTransport> ttransport(new TBufferedTransport(tsocket));  
	boost::shared_ptr<TProtocol> tprotocol(new TBinaryProtocol(ttransport)); 

	transport_client = ttransport;
	protocol_client = tprotocol;
}

  RetCode::type DialHandler:: systemCommand(const SysCommand::type cmdType)
  {
  	return RetCode::OK;
  }
  //RetCode::type isPrimary(const bool isPrimary);
  RetCode::type DialHandler:: addHealthGroup(const HealthGroupInfo& health, const std::string& policyName)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: delHealthGroup(const HealthGroupInfo& health, const std::string& policyName)
  {
  	return RetCode::OK;
  }
  //RetCode::type delHealthGroup(const HealthGroupInfo& health);
  RetCode::type DialHandler:: addHealthRecord(const HealthGroupInfo& health, const DialRecord& rec)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: modHealthRecord(const HealthGroupInfo& health, const DialRecord& rec)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: delHealthRecord(const HealthGroupInfo& health, const DialRecord& rec)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: addHealthPolicy(const HealthPolicyInfo& policy)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: modHealthPolicy(const HealthPolicyInfo& policy)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: delHealthPolicy(const HealthPolicyInfo& policy)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: dialServerConfig(const DialServerType::type typ, const bool allowed)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: addDialServer(const IpAddr& ip, const DialServerType::type typ)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: delDialServer(const IpAddr& ip, const DialServerType::type typ)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: addNginxGroup(const std::string& groupName, const std::string& policyName)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: delNginxGroup(const std::string& groupName, const std::string& policyName)
  {
  	return RetCode::OK;
  }
  //RetCode::type delNginxGroup(const std::string& groupName);
  RetCode::type DialHandler:: addNginxServer(const std::string& groupName, const DialNginxServer& server)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: modNginxServer(const std::string& groupName, const DialNginxServer& server)
  {
  	return RetCode::OK;
  }
  RetCode::type DialHandler:: delNginxServer(const std::string& groupName, const DialNginxServer& server)
  {
  	return RetCode::OK;
  }
  void DialHandler:: heartBeat(HeartBeatState& _return)
  {
  
  }
  RetCode::type DialHandler:: setServerState(const bool enable)
  {
  	return RetCode::OK;
  }


