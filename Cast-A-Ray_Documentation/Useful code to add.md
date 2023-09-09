# Thread count query 
```c++
#include <thread>
#include <vector>
#include <iostream>

void someFunction(int i) {
    std::cout << "Thread " << i << " is running!\n";
}

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    for(int i = 0; i < n; ++i) {
        threads.emplace_back(someFunction, i);
    }

    for(auto& thread : threads) {
        thread.join();
    }

    return 0;
}

```
# Entity class 
```c++
class Entity {
private:
    entt::entity handle;
    entt::registry* registry;
public:
    // Constructors, destructors, etc.

    template<typename T, typename... Args>
    void addComponent(Args&&... args) {
        registry->emplace<T>(handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& getComponent() {
        return registry->get<T>(handle);
    }

    template<typename T>
    void removeComponent() {
        registry->remove<T>(handle);
    }
};

```