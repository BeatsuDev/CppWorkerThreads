#include "worker.h"
#include <iostream>

using std::cout;

int main() {
    Workers worker_threads(4);
    Workers event_loop(1);

    worker_threads.start();
    event_loop.start();

    worker_threads.post([] {
        cout << "From inside the post!\n";
    });

    worker_threads.join();
    event_loop.join();
    return 0;
}