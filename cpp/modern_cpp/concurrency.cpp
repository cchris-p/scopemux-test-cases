/**
 * @file concurrency.cpp
 * @brief Examples of C++11 and later concurrency features
 *
 * This file demonstrates threads, mutexes, condition variables,
 * futures, promises, and other concurrency mechanisms in C++.
 */

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <queue>
#include <functional>
#include <chrono>

// Basic thread creation and joining
void basic_threading() {
    // Thread with function
    std::thread t1([]() {
        // Thread work here
        for (int i = 0; i < 10; ++i) {
            // Process
        }
    });
    
    // Thread with member function
    struct Worker {
        void process() {
            // Processing code
        }
    };
    
    Worker worker;
    std::thread t2(&Worker::process, &worker);
    
    // Join threads (wait for completion)
    t1.join();
    t2.join();
}

// Mutex for thread synchronization
class ThreadSafeCounter {
private:
    std::mutex mutex;
    int value = 0;
    
public:
    int increment() {
        std::lock_guard<std::mutex> lock(mutex);
        return ++value;
    }
    
    int get() {
        std::lock_guard<std::mutex> lock(mutex);
        return value;
    }
};

// Using unique_lock for more flexibility
void unique_lock_example() {
    std::mutex m;
    int shared_data = 0;
    
    auto worker = [&m, &shared_data](int val) {
        std::unique_lock<std::mutex> lock(m);
        shared_data += val;
        // Can unlock before lock scope ends
        lock.unlock();
        
        // Do other work...
        
        // Lock again
        lock.lock();
        shared_data *= 2;
    };
    
    std::thread t1(worker, 5);
    std::thread t2(worker, 10);
    
    t1.join();
    t2.join();
}

// Reader-writer lock (C++17)
class ThreadSafeCache {
private:
    std::shared_mutex mutex;
    std::unordered_map<std::string, std::string> cache;
    
public:
    std::string read(const std::string& key) {
        // Multiple threads can read simultaneously
        std::shared_lock<std::shared_mutex> lock(mutex);
        auto it = cache.find(key);
        return (it == cache.end()) ? "" : it->second;
    }
    
    void write(const std::string& key, const std::string& value) {
        // Only one thread can write at a time
        std::unique_lock<std::shared_mutex> lock(mutex);
        cache[key] = value;
    }
};

// Condition variables for thread coordination
class ThreadSafeQueue {
private:
    std::queue<int> queue;
    std::mutex mutex;
    std::condition_variable cv;
    
public:
    void push(int value) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(value);
        }
        // Notify one waiting thread
        cv.notify_one();
    }
    
    int pop() {
        std::unique_lock<std::mutex> lock(mutex);
        // Wait until queue is not empty
        cv.wait(lock, [this] { return !queue.empty(); });
        
        int value = queue.front();
        queue.pop();
        return value;
    }
};

// Futures and promises for asynchronous results
std::string fetch_data_async(const std::string& url) {
    // This would be executed in another thread
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return "Data from " + url;
}

void futures_example() {
    // Launch async task and get future
    std::future<std::string> result = std::async(std::launch::async, 
                                               fetch_data_async, 
                                               "example.com");
    
    // Do other work while waiting
    
    // Get result (will block until ready)
    std::string data = result.get();
}

// Manual promise/future
void promise_example() {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    std::thread worker([&promise] {
        // Do complex calculation
        int result = 42;
        promise.set_value(result);
    });
    
    // Wait for result
    int value = future.get();
    
    worker.join();
}

// Atomic variables for lock-free programming
void atomic_example() {
    std::atomic<int> counter(0);
    
    auto increment = [&counter]() {
        for (int i = 0; i < 1000; ++i) {
            counter++;  // Atomic operation
        }
    };
    
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    // counter will be exactly 2000
}

// Memory ordering with atomics
void memory_ordering_example() {
    std::atomic<int> data{0};
    
    // Relaxed ordering
    data.store(1, std::memory_order_relaxed);
    
    // Release-acquire ordering
    data.store(2, std::memory_order_release);
    int value = data.load(std::memory_order_acquire);
    
    // Sequential consistency
    data.store(3, std::memory_order_seq_cst);
}

// Thread-local storage
void thread_local_example() {
    thread_local int counter = 0;
    
    auto work = []() {
        // Each thread gets its own copy of counter
        thread_local int counter = 0;
        counter++;  // Only affects this thread's counter
    };
    
    std::thread t1(work);
    std::thread t2(work);
    
    t1.join();
    t2.join();
}

// Thread pool implementation
class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
    
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] { 
                            return this->stop || !this->tasks.empty(); 
                        });
                        
                        if (this->stop && this->tasks.empty())
                            return;
                        
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    
                    task(); // Execute the task
                }
            });
        }
    }
    
    // Add new task to the pool
    template<class F>
    auto enqueue(F&& f) {
        using return_type = std::invoke_result_t<F>;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::forward<F>(f)
        );
        
        std::future<return_type> res = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            
            // Don't allow enqueueing after stopping the pool
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
                
            tasks.emplace([task]() { (*task)(); });
        }
        
        condition.notify_one();
        return res;
    }
    
    // Destructor joins all threads
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        
        condition.notify_all();
        
        for (std::thread &worker : workers)
            worker.join();
    }
};
