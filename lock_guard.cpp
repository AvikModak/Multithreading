#include <iostream>
#include <thread>
#include <mutex>

class Counter {
    
private:
    int count;
    std::mutex mtx; // Mutex to protect access to 'count'

public:
    Counter() : count(0) {}
    
    // Thread-safe method to increment the counter
    void increment() {
        std::lock_guard<std::mutex> lock(mtx); // Locks the mutex for thread-safe access
        ++ count;
        std::cout<< "Count after increment = "<< count << "\n";
    }
    
    // Thread-safe method to get the current counter value
    int getCount() {
        std::lock_guard<std::mutex> lock(mtx); // Locks the mutex for thread-safe access
        return count;
    }
};

void threadTask (Counter &counter) {
    for (int i=0; i < 5; ++i) {
        counter.increment();
    }
}

int main() {
    Counter counter;
    
    std::thread t1(threadTask, std::ref(counter)); // Start first thread
    std::thread t2(threadTask, std::ref(counter)); // Start second thread
    
    t1.join(); // Wait for first thread to finish
    t2.join(); // Wait for second thread to finish
    
    std::cout<< "Final count = "<< counter.getCount() <<"\n";
    
    return 0;
}
