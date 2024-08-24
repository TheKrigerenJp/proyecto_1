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

    //Método para agregar un nodo al final de la lista
    void append(const T& value) {
        MPointer<Node> newNode = MPointer<Node>::New();
        *newNode = Node(value);
        if (tail) {
            (*tail)->next = newNode;
            (*newNode)->prev = tail;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
    }

    // Método para agregar un nodo al inicio de la lista
    void prepend(const T& value) {
        MPointer<Node> newNode = MPointer<Node>::New();
        *newNode = Node(value);
        if (head) {
            (*head)->prev = newNode;
            (*newNode)->next = head;
            head = newNode;
        } else {
            head = tail = newNode;
        }
    }

    // Método para eliminar un nodo específico
    void remove(const T& value) {
        MPointer<Node> current = head;
        while (current) {
            if (**((*current)->data) == value) {
                if ((*current)->prev) {
                    (*(*current)->prev)->next = (*current)->next;
                } else {
                    head = (*current)->next;
                }
                if ((*current)->next) {
                    (*(*current)->next)->prev = (*current)->prev;
                } else {
                    tail = (*current)->prev;
                }
                break;
            }
            current = (*current)->next;
        }
    }

    // Método para buscar un valor en la lista
    bool find(const T& value) const {
        MPointer<Node> current = head;
        while (current) {
            if (**((*current)->data) == value) {
                return true;
            }
            current = (*current)->next;
        }
        return false;
    }

    // Método para mostrar la lista
    void display() const {
        MPointer<Node> current = head;
        while (current) {
            std::cout << **((*current)->data) << " ";
            current = (*current)->next;
        }
        std::cout << std::endl;
    }

    // Método para mostrar la lista en orden inverso
    void displayReverse() const {
        MPointer<Node> current = tail;
        while (current) {
            std::cout << **((*current)->data) << " ";
            current = (*current)->prev;
        }
        std::cout << std::endl;
    }

    // Método para obtener el tamaño de la lista
    int size() const {
        int count = 0;
        MPointer<Node> current = head;
        while (current) {
            count++;
            current = (*current)->next;
        }
        return count;
    }

    // Método para vaciar la lista
    void clear() {
        head = nullptr;
        tail = nullptr;
    }

};


//Ahora vamos a hacer la función para probar la lista doblemente enlazada :D
int main() {
    MPointerGC::getInstance().startGC();

    ListaDoble<int> lista;
    lista.append(5);
    lista.append(3);
    lista.append(10);
    lista.append(7);
    lista.append(8);
    lista.append(12);

    std::cout << "Lista original: ";
    lista.display();

    std::cout << "Lista en orden inverso: ";
    lista.displayReverse();

    std::cout << "Tamaño de la lista: " << lista.size() << std::endl;

    lista.prepend(2);
    std::cout << "Lista después de prepend 2: ";
    lista.display();

    lista.remove(5);
    std::cout << "Lista después de eliminar 5: ";
    lista.display();

    std::cout << "Buscar 10: " << (lista.find(10) ? "Encontrado" : "No encontrado") << std::endl;
    std::cout << "Buscar 8: " << (lista.find(8) ? "Encontrado" : "No encontrado") << std::endl;

    lista.clear();
    std::cout << "Lista después de limpiar: ";
    lista.display();
    std::cout << "Tamaño de la lista: " << lista.size() << std::endl;

    MPointerGC::getInstance().stopGC();
    return 0;

}