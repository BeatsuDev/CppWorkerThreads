#include "workers.h"
#include <list>
#include <thread>
#include <iostream>
#include <mutex>
#include <functional>

std::mutex cout_lock;

void worker(int i) {
    const std::lock_guard<std::mutex> lock(cout_lock);
    std::cout << "Hello from thread " << i << "\n";
}

Workers::Workers(int worker_count) {
    for (int i = 0; i < worker_count; i++) {
        worker_threads.emplace_back(std::thread(worker, i));
    }

    return;
}

void Workers::post(std::function<void()> task) {

}

void Workers::join() {
    std::cout << "Joining all threads!\n";
    for (std::thread &t : worker_threads) {
        t.join();
    }
}