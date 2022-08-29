/*
 * @Author: JasonLaw
 * @Date: 2022-05-08 11:00:38
 * @LastEditors: JasonLaw
 * @LastEditTime: 2022-08-15 21:07:23
 * @FilePath: /WebServer/code/buffer/buffer.h
 * @Description:
 */
#ifndef BUFFER_H
#define BUFFER_H
#include <assert.h>
#include <sys/uio.h> //readv
#include <unistd.h>  // write

#include <atomic>
#include <cstring> //perror
#include <iostream>
#include <vector> //readv
class Buffer {
  public:
    Buffer(int initBuffSize = 1024);
    ~Buffer() = default;

    size_t WritableBytes() const;
    size_t ReadableBytes() const;
    size_t PrependableBytes() const;

    const char *Peek() const;
    void EnsureWriteable(size_t len);
    void HasWritten(size_t len);

    void Retrieve(size_t len);
    void RetrieveUntil(const char *end);

    void RetrieveAll();
    std::string RetrieveAllToStr();

    const char *BeginWriteConst() const;
    char *BeginWrite();

    void Append(const std::string &str);
    void Append(const char *str, size_t len);
    void Append(const void *data, size_t len);
    void Append(const Buffer &buff);

    ssize_t ReadFd(int fd, int *Errno);
    ssize_t WriteFd(int fd, int *Errno);

  private:
    char *BeginPtr_();
    const char *BeginPtr_() const;
    void MakeSpace_(size_t len);

    std::vector<char> buffer_;          // 具体装数据的vector
    std::atomic<std::size_t> readPos_;  // 读的位置
    std::atomic<std::size_t> writePos_; // 写的位置
};

#endif // BUFFER_H