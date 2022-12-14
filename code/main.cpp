/**
 * @file main.cpp
 * @author JasonLaw (luozuxuan@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <unistd.h>

#include "server/webserver.h"

int main() {
  /* 守护进程 后台运行 */
  // daemon(1, 0);

  WebServer server(1316, 3, 60000, false, /* 端口 ET模式 timeoutMs 优雅退出  */
                   3306, "root", "qwer1234", "webserver", /* Mysql配置 */
                   12, 6, true, 1, /* 连接池数量 线程池数量 日志开关 日志等级 */
                   1024); /* 日志异步队列容量 */

  server.Start();
}
