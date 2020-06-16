/* #define _LOG4CPP_ */
/* #include "../include/MyLog.hpp" */
#include "../include/WordQueryServer.hpp"
#include "../include/Configuration.hpp"
/* #include "../include/TimerThread.hpp" */
#include <stdio.h>
#include <string>
#include <json/json.h>

using std::string;

namespace lys
{

WordQueryServer::WordQueryServer(Configuration &conf)
:_conf(conf)
,_tcpServer(conf.getConfigMap()["serverIP"],stoi(conf.getConfigMap()["port"]))
,_threadpool(stoi(conf.getConfigMap()["threadpoolCap"]),
             stoi(conf.getConfigMap()["taskQueSize"]))
,_wordQuery(conf)
/* ,_timer(std::bind(&CacheManger::periodicUpdate,CacheManger::getInstance(), */
/*                   _conf.getConfigMap()["cachePath"]),3,6) */
{
    cout << "WordQueryServer(Configuration &, SplitTool *)" << endl;
    /* _timer.start(); */
}
 
WordQueryServer::~WordQueryServer()
{
    /* _timer.stop(); */
}
void WordQueryServer::onConnection(const TcpConnectionPtr &conn)
{
    printf("%s has connectd!\n",conn->toString().c_str());
    /* LogInfo("%s has connectd!\n",conn->toString().c_str()); */
    /* conn->send("welcome to server."); */
}

void WordQueryServer::onMessage(const TcpConnectionPtr &conn)
{
    /* int32_t len = conn->recvInt32(); */
    
    /* printf("len=%d\n",len); */
    /* char buff[1024]={0}; */
    /* conn->receiveN(buff,len); */
    //json解码
    /* Json::Value root; */
    /* Json::Reader reader; */

    /* if(!reader.parse(buff,root)){ */
    /*     /1* printf("Json parse fail!\n"); *1/ */
    /*     LogError("Json parse fail!\n"); */
    /*     return; */
    /* } */
    
    /* printf("buf=%s\n",buff); */
    /* int i=0; */
    /* string msg = root["queryWord"][i].asString(); */
    /* printf("msg=%s\n",msg.c_str()); */
    string msg = conn -> receive();
    size_t pos = msg.find('\n');
    msg = msg.substr(0, pos);
    /* LogInfo("client send: %s, size: %lu", msg.c_str(), msg.size()); */
    _threadpool.addTask(std::bind(&WordQueryServer::doTaskThread, this, conn, msg));
}

void WordQueryServer::onClose(const TcpConnectionPtr &conn)
{
    printf("%s has closed!\n",conn->toString().c_str());
    /* LogInfo("%s has closed!\n",conn->toString().c_str()); */
}

void WordQueryServer::start()
{

    /* CacheManger* pCacheManger = CacheManger::getInstance(); */
    /* pCacheManger->init(stoi(_conf.getConfigMap()["threadpoolCap"]), */ 
    /*                     _conf.getConfigMap()["cachePath"]); */

    _threadpool.start();
 
    using namespace std::placeholders;

    _tcpServer.setConnectionCallback(std::bind(&WordQueryServer::onConnection,this,_1));
    _tcpServer.setMessageCallback(std::bind(&WordQueryServer::onMessage,this,_1));
    _tcpServer.setCloseCallback(std::bind(&WordQueryServer::onClose,this,_1));
     
    _tcpServer.start();

}
void WordQueryServer::doTaskThread(const TcpConnectionPtr &conn, const std::string &msg)
{
    string ret = _wordQuery.doQuery(msg);
    int sz = ret.size();
    string message(std::to_string(sz));
    message.append("\n").append(ret);
    conn->sendInLoop(message);
}

}//end of namespace lys
