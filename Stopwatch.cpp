#include <iostream>
#include <chrono>
#include <string>
#include <thread>

class Stopwatch
{
public:
    using clock = std::chrono::steady_clock;
    void start()
    {
        if (!running_)
        {
            start_ = clock::now();
            running_ = true;
        }
    }
    void stop()
    {
        if (running_)
        {
            elapsed_ += clock::now() - start_;
            running_ = false;
        }
    }
    void reset()
    {
        elapsed_ = clock::duration{};
        if (running_)
            start_ = clock::now();
    }
    double elapsed_seconds() const
    {
        auto total = elapsed_;
        if (running_)
            total += clock::now() - start_;
        return std::chrono::duration<double>(total).count();
    }

private:
    clock::time_point start_;
    clock::duration elapsed_{};
    bool running_ = false;
};
