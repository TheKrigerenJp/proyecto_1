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

template <typename T>
class MPointer {
public:
    static MPointer<T> New() {
        T* ptr = new T();
        MPointer<T> mp(ptr);
        MPointerGC::getInstance().registerPointer(ptr);
        return mp;
    }

    ~MPointer() {
        MPointerGC::getInstance().deregisterPointer(ptr_);
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    MPointer<T>& operator=(const T& value) {
        *ptr_ = value;
        return *this;
    }

    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            MPointerGC::getInstance().increaseReference(other.ptr_);
            MPointerGC::getInstance().decreaseReference(ptr_);
            ptr_ = other.ptr_;
        }
        return *this;
    }

    T operator&() const {
        return *ptr_;
    }

private:
    MPointer(T* ptr) : ptr_(ptr) {}

    T* ptr_;
};

template <typename T>
class ListaDoble {
    struct Node {
        MPointer<T> data;
        MPointer<Node> next;
        MPointer<Node> prev;

        Node(const T& value) : data(MPointer<T>::New()) {

        }
    };

    MPointer<Node> head;
    MPointer<Node> tail;

public:
    ListaDoble() : head(nullptr), tail(nullptr) {}


    //Aqui agregaré los metodos de las listas doblemente enlazadas que pondré despues
};