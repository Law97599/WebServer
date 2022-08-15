/*
 * @Author: JasonLaw
 * @Date: 2022-05-08 11:00:38
 * @LastEditors: JasonLaw
 * @LastEditTime: 2022-08-15 21:03:30
 * @FilePath: /WebServer/code/server/epoller.h
 * @Description:
 */
#ifndef EPOLLER_H
#define EPOLLER_H

#include <assert.h>  // close()
#include <errno.h>
#include <fcntl.h>      // fcntl()
#include <sys/epoll.h>  //epoll_ctl()
#include <unistd.h>     // close()

#include <vector>

class Epoller {
 public:
  explicit Epoller(int maxEvent = 1024);

  ~Epoller();

  bool AddFd(int fd, uint32_t events);

  bool ModFd(int fd, uint32_t events);

  bool DelFd(int fd);

  int Wait(int timeoutMs = -1);

  int GetEventFd(size_t i) const;

  uint32_t GetEvents(size_t i) const;

 private:
  int epollFd_;  // epoll_create()创建一个epoll对象，返回值就是epollFd

  std::vector<struct epoll_event> events_;  // 检测到的事件的集合
};

#endif  // EPOLLER_H