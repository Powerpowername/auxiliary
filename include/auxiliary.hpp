#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <string>
#include <functional>
#include <utility>
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
