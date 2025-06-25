/**
 * @file memory_management.cpp
 * @brief Examples of modern C++ memory management techniques
 *
 * This file demonstrates smart pointers, RAII patterns, and other
 * memory management features in modern C++.
 */

#include <memory>
#include <vector>
#include <string>
#include <functional>

// Basic Resource class for demonstration
class Resource {
private:
    std::string name;
    size_t size;

public:
    Resource(const std::string& n, size_t s) : name(n), size(s) {
        // Constructor logic - resource acquisition
    }

    ~Resource() {
        // Destructor logic - resource release
    }

    void use() {
        // Implementation
    }
};

// RAII wrapper example
class ResourceGuard {
private:
    Resource* resource;

public:
    ResourceGuard(const std::string& name, size_t size) {
        resource = new Resource(name, size);
    }

    ~ResourceGuard() {
        delete resource;
    }

    // Delete copy constructors/assignment
    ResourceGuard(const ResourceGuard&) = delete;
    ResourceGuard& operator=(const ResourceGuard&) = delete;

    // Allow move semantics
    ResourceGuard(ResourceGuard&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;
    }

    ResourceGuard& operator=(ResourceGuard&& other) noexcept {
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }

    Resource* get() {
        return resource;
    }
};

// Smart pointer examples
void smart_pointer_examples() {
    // unique_ptr - exclusive ownership
    std::unique_ptr<Resource> uniqueRes = std::make_unique<Resource>("UniqueResource", 100);
    uniqueRes->use();

    // Moving unique_ptr
    std::unique_ptr<Resource> movedRes = std::move(uniqueRes);
    // uniqueRes is now null

    // shared_ptr - shared ownership
    std::shared_ptr<Resource> sharedRes1 = std::make_shared<Resource>("SharedResource", 200);
    {
        std::shared_ptr<Resource> sharedRes2 = sharedRes1; // Reference count = 2
        sharedRes2->use();
    } // Reference count = 1

    // weak_ptr - non-owning reference
    std::weak_ptr<Resource> weakRes = sharedRes1;
    if (auto locked = weakRes.lock()) {
        // Resource is still valid
        locked->use();
    }

    // shared_ptr with custom deleter
    auto customDeleter = [](Resource* ptr) {
        // Custom cleanup
        delete ptr;
    };
    std::shared_ptr<Resource> customRes(new Resource("CustomDeleted", 300), customDeleter);
}

// Circular reference problem and solution
struct Node {
    std::string value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Using weak_ptr to break circular reference

    Node(const std::string& v) : value(v) {}
};

void circular_reference_example() {
    auto node1 = std::make_shared<Node>("Node1");
    auto node2 = std::make_shared<Node>("Node2");

    // Create circular reference without memory leak
    node1->next = node2;
    node2->prev = node1; // weak_ptr doesn't increase reference count
}

// Scope guard pattern
template <typename Func>
class ScopeGuard {
private:
    Func cleanup;
    bool active;

public:
    ScopeGuard(Func f) : cleanup(std::move(f)), active(true) {}

    ~ScopeGuard() {
        if (active) {
            cleanup();
        }
    }

    void dismiss() {
        active = false;
    }

    // Delete copy operations
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    // Allow move operations
    ScopeGuard(ScopeGuard&& other) noexcept 
        : cleanup(std::move(other.cleanup)), active(other.active) {
        other.active = false;
    }
};

// Factory function for scope guards
template <typename Func>
ScopeGuard<Func> make_scope_guard(Func f) {
    return ScopeGuard<Func>(std::move(f));
}

// Demonstrating scope guard usage
void scope_guard_example() {
    // Resource that needs cleanup
    int* data = new int[100];

    // Setup automatic cleanup
    auto guard = make_scope_guard([&] {
        delete[] data;
    });

    // If an exception occurs, data will still be cleaned up
    // If we complete successfully, we can dismiss the guard
    // guard.dismiss(); 
}

// Memory pool example
class MemoryPool {
private:
    struct Block {
        char* data;
        size_t size;
        Block* next;
    };

    Block* head;
    size_t blockSize;

public:
    MemoryPool(size_t initialSize = 4096) : head(nullptr), blockSize(initialSize) {
        allocateBlock();
    }

    ~MemoryPool() {
        while (head) {
            Block* temp = head;
            head = head->next;
            delete[] temp->data;
            delete temp;
        }
    }

    void* allocate(size_t size) {
        // Simplified allocation strategy
        if (!head || head->size < size) {
            allocateBlock(std::max(size, blockSize));
        }

        void* result = head->data + head->size - size;
        head->size -= size;
        return result;
    }

    // Cannot free individual allocations in this simple implementation
    // In a real pool, would implement freelist

private:
    void allocateBlock(size_t size = 0) {
        Block* newBlock = new Block;
        newBlock->size = size > 0 ? size : blockSize;
        newBlock->data = new char[newBlock->size];
        newBlock->next = head;
        head = newBlock;
    }

    // Delete copy and move operations
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    MemoryPool(MemoryPool&&) = delete;
    MemoryPool& operator=(MemoryPool&&) = delete;
};
