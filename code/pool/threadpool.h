/*
 * @Author: JasonLaw
 * @Date: 2022-05-08 11:00:38
 * @LastEditors: JasonLaw
 * @LastEditTime: 2022-08-15 21:03:48
 * @FilePath: /WebServer/code/pool/threadpool.h
 * @Description:
 */
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
class ThreadPool {
  public:
    explicit ThreadPool(size_t threadCount = 8)
        : pool_(std::make_shared<Pool>()) {
        assert(threadCount > 0);

        // 创建threadCount个子线程
        for (size_t i = 0; i < threadCount; i++) {
            std::thread([pool = pool_] {
                std::unique_lock<std::mutex> locker(pool->mtx);
                while (true) {
                    if (!pool->tasks.empty()) {
                        // 从任务队列中取一个任务
                        auto task = std::move(pool->tasks.front());
                        // 移除掉
                        pool->tasks.pop();
                        locker.unlock();
                        task();
                        locker.lock();
                    } else if (pool->isClosed)
                        break;
                    else
                        pool->cond.wait(locker);
                }
            }).detach(); // 线程分离
        }
    }

    ThreadPool() = default;

    ThreadPool(ThreadPool &&) = default;

    ~ThreadPool() {
        if (static_cast<bool>(pool_)) {
            {
                std::lock_guard<std::mutex> locker(pool_->mtx);
                pool_->isClosed = true;
            }
            pool_->cond.notify_all();
        }
    }

    template<class F>
    void AddTask(F &&task) {
        {
            std::lock_guard<std::mutex> locker(pool_->mtx);
            pool_->tasks.emplace(std::forward<F>(task));
        }
        pool_->cond.notify_one();
    }

  private:
    // 结构体，池子
    struct Pool {
        std::mutex mtx;                          // 互斥锁
        std::condition_variable cond;            // 条件变量
        bool isClosed;                           // 是否关闭
        std::queue<std::function<void()>> tasks; // 队列（保存的是任务）
    };
    std::shared_ptr<Pool> pool_; //  池子
};

#endif // THREADPOOL_H