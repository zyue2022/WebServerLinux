/*
 * @Description  : epoll实例类
 * @Date         : 2022-07-16 01:14:05
 * @LastEditTime : 2022-07-18 00:02:01
 */
#ifndef EPOLLER_H
#define EPOLLER_H

#include <assert.h>
#include <errno.h>
#include <fcntl.h> /*fcntl*/
#include <sys/epoll.h>
#include <unistd.h>

#include <vector>

class Epoller {
private:
    int epollFd_;  // EPOLL自己对应的文件描述符

    std::vector<epoll_event> events_;  // EPOLL事件表

public:
    explicit Epoller(int maxEvent = 1024);
    ~Epoller();

    bool addFd(int fd, uint32_t events);
    bool modFd(int fd, uint32_t events);
    bool delFd(int fd);

    int wait(int timeoutMS = -1);

    int      getEventFd(size_t i) const;
    uint32_t getEvents(size_t i) const;
};

#endif  //EPOLLER_H
