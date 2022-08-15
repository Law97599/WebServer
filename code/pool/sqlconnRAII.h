/*
 * @Author: JasonLaw
 * @Date: 2022-05-08 11:00:38
 * @LastEditors: JasonLaw
 * @LastEditTime: 2022-08-15 21:03:52
 * @FilePath: /WebServer/code/pool/sqlconnRAII.h
 * @Description:
 */
#ifndef SQLCONNRAII_H
#define SQLCONNRAII_H
#include "sqlconnpool.h"

/* 资源在对象构造初始化 资源在对象析构时释放*/
class SqlConnRAII {
 public:
  SqlConnRAII(MYSQL** sql, SqlConnPool* connpool) {
    assert(connpool);
    *sql = connpool->GetConn();
    sql_ = *sql;
    connpool_ = connpool;
  }

  ~SqlConnRAII() {
    if (sql_) {
      connpool_->FreeConn(sql_);
    }
  }

 private:
  MYSQL* sql_;
  SqlConnPool* connpool_;
};

#endif  // SQLCONNRAII_H