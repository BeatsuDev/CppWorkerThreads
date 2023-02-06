#ifndef WORKERS_H
#define WORKERS_H

#include <functional>
#include <thread>
#include <list>
#include <atomic>
#include <mutex>

class Workers {
    std::list<std::function<void()>> task_list;
    std::list<std::thread> threads();
    public:
        Workers(int worker_count);
        void start();
        void post(std::function<void()> task);
        void join();
};

class Worker {
    std::list<std::function<void()>> &task_list;
    std::atomic<bool> keep_running;
    mutex task_lock;
    public:
        Worker();
        void run();
        void join();
};

#endif