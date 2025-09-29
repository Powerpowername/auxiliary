#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <deque>
#include <future>
// using namespace std::chrono;//不适用命名空间防止和MSVC使用的时候因文件格式而产生格式问题


namespace auxi
{
    namespace clock
    {

        class blockClock
        {
        protected:
            std::chrono::high_resolution_clock::time_point start_time;
            std::chrono::high_resolution_clock::time_point end_time;
            std::chrono::milliseconds duration = std::chrono::milliseconds(0);
            bool isRunning = false;
            std::mutex mtx;

        public:
            template <typename Callback, typename... Args>
            // void untilTime(double timeMs,std::function<R(Args...)> callback,Args&&... args)
            void untilTime(double timeMs, Callback &&callback, Args &&...args)

            {
                // 防止多次调用产生的未定义行为
                std::unique_lock<std::mutex> lck(mtx);
                if (isRunning == false)
                    isRunning = true;
                else
                    return;
                start_time = std::chrono::high_resolution_clock::now();
                while (static_cast<double>(duration.count()) < timeMs)
                {
                    end_time = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    std::cout << "time: " << duration.count() << std::endl;
                }
                callback(std::forward<Args>(args)...);
            }
        };
    } // namespace name

}


namespace auxi
{
    namespace threadPool
    {
        class threadPool
        {
        protected:
            std::vector<std::thread> workQueue;
            //使用万能指针，指向工作函数
            std::deque<void*> tasks;
            int32_t threadNum;
            std::mutex mtx;
            std::condition_variable cv;
        public:
            void worker()
            {
                while(true)
                {

                }
            }
            threadPool(int32_t threadNum = 10) : threadNum(threadNum)
            {
                for (int i = 0; i < threadNum; i++)
                {
                    workQueue.push_back(std::thread());
                }
                
            }

            // 添加任务至工作队列
            template <typename Callback, typename... Args>
             auto addTask(Callback&& callback, Args&&... args)->std::future<decltype(f(args...))>
            {
                std::unique_lock<std::mutex> lck(mtx);
                std::packaged_task
                auto task = std::bind(std::forward<Callback>(callback), std::forward<Args>(args)...);
                tasks.push_back(task);
                cv.notify_one();
            }
            
            void execute()
            {
                while(true)
                {

                }
            }



        };
    }
}