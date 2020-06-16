#ifndef __WORDQUERYSERVER_HPP__
#define __WORDQUERYSERVER_HPP__

#include "TcpServer.hpp"
#include "Threadpool.hpp"
#include "WordQuery.hpp"
/* #include "TimerThread.hpp" */

namespace lys
{
class Configuration;
class TcpConnection;

class WordQueryServer
{
public:
    WordQueryServer(Configuration &conf);
    ~WordQueryServer();
    void start();
private:
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn);
    void onClose(const TcpConnectionPtr &conn);
    void doTaskThread(const TcpConnectionPtr &conn, const std::string &msg);
 
private:
    Configuration &_conf;
    TcpServer _tcpServer; //IO线程
    Threadpool _threadpool; //计算线程
    WordQuery _wordQuery;
    /* TimerThread _timer; */ 

};

}//end of namespace lys

#endif
