<!--
 * @Author: JasonLaw
 * @Date: 2022-05-08 11:00:38
 * @LastEditors: JasonLaw
 * @LastEditTime: 2022-08-17 23:06:15
 * @FilePath: /WebServer/readme.md
 * @Description: 
-->
# WebServer
用C++实现的高性能WEB服务器，经webbench压力测试工具测试，可以实现上万的QPS。

## 项目亮点
* 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型；
* 利用正则表达式与有限状态机解析HTTP请求报文，实现处理静态资源的请求；
* 利用标准库容器封装char，实现自动增长的缓冲区；
* 基于堆实现的定时器，关闭超时的非活动连接；
* 利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；
* 利用RAII机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。

## 环境要求
* Linux
* C++14
* MySql

## 项目结构
```
.
├── code           源代码
│   ├── buffer
│   ├── config
│   ├── http
│   ├── log
│   ├── timer
│   ├── pool
│   ├── server
│   └── main.cpp
├── test           单元测试
│   ├── Makefile
│   └── test.cpp
├── resources      静态资源
│   ├── index.html
│   ├── image
│   ├── video
│   ├── js
│   └── css
├── bin            可执行文件
│   └── server
├── log            日志文件
├── webbench-1.5   压力测试
├── build          
│   └── Makefile
├── Makefile
├── LICENSE
└── readme.md
```


## 项目启动
需要先创建好数据库
```bash
// 建立yourdb库
create database yourdb;

// 创建user表
USE yourdb;
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;

// 添加数据
INSERT INTO user(username, password) VALUES('name', 'password');
```

```bash
make
./bin/server
```

## 压力测试
![image-webbench](https://github.com/markparticle/WebServer/blob/master/readme.assest/PressTest.png)
```bash
./webbench-1.5/webbench -c 100 -t 10 http://ip:port/
./webbench-1.5/webbench -c 1000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 5000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 10000 -t 10 http://ip:port/
```
* 测试环境: 
Ubuntu: 20.04 
cpu: Intel(R) Xeon(R) CPU E5-2620 v3 @ 2.40GHz
mem: 64G 
* QPS 10000+
