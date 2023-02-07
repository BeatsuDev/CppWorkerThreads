#include <list>
#include <thread>
#include <functional>

class Workers {
    private:
        std::list<std::thread> worker_threads;
        std::list<std::function<void()>> task_list;

    public:
        Workers(int worker_count);
        // void start();
        void post(std::function<void()>);
        void join();
};