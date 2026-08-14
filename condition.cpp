#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <vector>

// 先看这个类“依赖什么”，再看“能对外提供什么功能”
template <typename T>
class ThreadSafeQueue
{
private:
    std::queue<T> q_;            // 真正存数据的缓冲区
    std::mutex m_;               // 保护 q_ 的锁
    std::condition_variable cv_; // 让消费者等待 / 被唤醒
    bool done_ = false;          // 生产者结束后的关闭标志

public:
    // 生产者：放一个元素进去，并通知等待中的消费者
    void push(T value)
    {
        {
            std::lock_guard<std::mutex> lock(m_);
            q_.push(std::move(value));
        }
        cv_.notify_one();
    }

    // 消费者：等待直到队列里有数据，或者生产者宣布结束
    std::optional<T> pop_wait()
    {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [&]
                 { return !q_.empty() || done_; });

        // 队列空且 done_ == true，表示生产者已经结束，不再有新数据
        if (q_.empty())
        {
            return std::nullopt;
        }

        T value = std::move(q_.front());
        q_.pop();
        return value;
    }

    // 生产者结束：设置 done_，并唤醒所有等待中的消费者
    void shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(m_);
            done_ = true;
        }
        cv_.notify_all();
    }
};

int main()
{
    ThreadSafeQueue<int> q;

    // 生产者：先放入 1~50，再通知所有消费者结束
    std::thread producer([&]
                         {
        for (int i = 1; i <= 50; ++i) {
            q.push(i);
        }
        q.shutdown(); });

    // 3 个消费者：不停取值，直到收到 shutdown 的结束信号
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; ++i)
    {
        consumers.emplace_back([&]
                               {
            while (true) {
                auto item = q.pop_wait();
                if (!item) {
                    break;
                }

                std::cout << "thread " << std::this_thread::get_id()
                          << " got " << *item << '\n';
            } });
    }

    producer.join();
    for (auto &consumer : consumers)
    {
        consumer.join();
    }

    return 0;
}