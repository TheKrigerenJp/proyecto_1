#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <unordered_map>

// Clase MPointerGC para la gestión de memoria
class MPointerGC {
public:
    static MPointerGC& getInstance() {
        static MPointerGC instance;
        return instance;
    }

    template <typename T>
    void registerPointer(T* ptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        pointers_[ptr] = 1;
    }

    template <typename T>
    void deregisterPointer(T* ptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        pointers_.erase(ptr);
    }

    template <typename T>
    void increaseReference(T* ptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        pointers_[ptr]++;
    }

    template <typename T>
    void decreaseReference(T* ptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (--pointers_[ptr] == 0) {
            delete ptr;
            pointers_.erase(ptr);
        }
    }

    void startGC() {
        gcThread_ = std::thread([this]() {
            while (running_) {
                std::this_thread::sleep_for(std::chrono::seconds(gcInterval_));
                collectGarbage(); // Llamada al método de recolección de basura
            }
        });
    }

    void stopGC() {
        running_ = false;
        if (gcThread_.joinable()) {
            gcThread_.join();
        }
    }

private:
    MPointerGC() : running_(true), gcInterval_(10) {}
    ~MPointerGC() {
        stopGC();
    }

    void collectGarbage() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto it = pointers_.begin(); it != pointers_.end();) {
            if (it->second == 0) {
                delete it->first;
                it = pointers_.erase(it);
            } else {
                ++it;
            }
        }
    }



    std::unordered_map<void*, int> pointers_;
    std::mutex mutex_;
    bool running_;
    int gcInterval_;
    std::thread gcThread_;
};