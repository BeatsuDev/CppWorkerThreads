#include "worker.h"
#include <iostream>
#include <functional>

Workers::Workers(int worker_count) {
    for (int i = 0; i < worker_count; i++) {
        (this->threads).emplace_back(std::thread);
    }
    std::cout << "I got created!\n";
}

void Workers::start() {
    std::cout << "I started!\n";
}

void Workers::post(std::function<void()> task) {
    std::cout << "Posted!\n";
}

void Workers::join() {
    this->keep_running_threads = false;
    for (&t : this->threads) {
        t.join();
    }
    std::cout << "Joined ya!\n";
}

void Worker::Worker(std::list<std::function<void()>> task_list) {
    this->task_list = *task_list;
    this->keep_running = true;
}

void Worker::run() {
    while (this->keep_running) {
        std::function<void> task;
        if (!this->task_list.empty()) {
            lock_guard<std::mutex> lock(task_lock);
            this->task_list.pop_front();
            task = this->task_list.front();
        }
        task();
    }
}

void Worker::join() {
    this->keep_running = false;
}