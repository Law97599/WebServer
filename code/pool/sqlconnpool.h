/*
 * @Author: JasonLaw
 * @Date: 2022-05-08 11:00:38
 * @LastEditors: JasonLaw
 * @LastEditTime: 2022-08-15 21:03:54
 * @FilePath: /WebServer/code/pool/sqlconnpool.h
 * @Description:
 */
#ifndef SQLCONNPOOL_H
#define SQLCONNPOOL_H

#include <mysql/mysql.h>
#include <semaphore.h>

#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "../log/log.h"

class SqlConnPool {
  public:
    static SqlConnPool *Instance();

    MYSQL *GetConn();
    void FreeConn(MYSQL *conn);
    int GetFreeConnCount();

    void Init(
        const char *host,
        int port,
        const char *user,
        const char *pwd,
        const char *dbName,
        int connSize);
    void ClosePool();

  private:
    SqlConnPool();
    ~SqlConnPool();

    int MAX_CONN_;  // 最大连接数
    int useCount_;  // 当前连接数
    int freeCount_; // 空闲连接数

    std::queue<MYSQL *> connQue_; // 队列
    std::mutex mtx_;              // 互斥锁
    sem_t semId_;                 // 信号量
};

#endif // SQLCONNPOOL_H