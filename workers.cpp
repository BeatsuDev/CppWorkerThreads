#include "workers.h"
#include <atomic>
#include <mutex>
#include <list>
#include <thread>
#include <iostream>
#include <functional>

std::mutex cout_lock;
std::mutex task_lock;

void worker(int i, std::atomic<bool> &running, std::list<std::function<void()>> &task_list) {
    {
        const std::lock_guard<std::mutex> lock(cout_lock);
        std::cout << "Hello from thread " << i << "\n";
    }
    while (running) {
        const std::lock_guard<std::mutex> lock(task_lock);
        /*
        std::function<void()> task;
        if (!task_list.empty()) {
            task = task_list.front();
            task_list.pop_front();
        }
        task();
        */
    }
}

Workers::Workers(int worker_count) {
    running = true;
    for (int i = 0; i < worker_count; i++) {
        worker_threads.emplace_back(std::thread(worker, i, std::ref(running), std::ref(task_list)));
    }
    return;
}

void Workers::post(std::function<void()> task) {

}

void Workers::join() {
    std::cout << "Joining all threads!\n";
    running = false;
    for (std::thread &t : worker_threads) {
        t.join();
    }
}