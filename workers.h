#include <list>
#include <thread>
#include <functional>
#include <atomic>

class Workers {
    private:
        std::list<std::thread> worker_threads;
        std::list<std::function<void()>> task_list;
        std::atomic<bool> running;

    public:
        Workers(int worker_count);
        // void start();
        void post(std::function<void()>);
        void join();
};