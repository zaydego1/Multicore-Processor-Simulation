#ifndef MEMSTACK_H
#define MEMSTACK_H

#include <stack>
#include <string>
#include <mutex>

class MemStack {
public:
    // Get the singleton instance of the stack
    static MemStack& getInstance() {
        static MemStack instance;
        return instance;
    }

    // Push a string onto the stack
    void push(const std::string& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        stack_.push(value);
    }

    // Pop a string off the stack
    std::string pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (stack_.empty()) {
            return "";
        }
        std::string value = stack_.top();
        stack_.pop();
        return value;
    }

    // Check if the stack is empty
    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return stack_.empty();
    }

    // Get the size of the stack
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return stack_.size();
    }

    std::string top() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (stack_.empty()) {
            return "";
        }
        return stack_.top();
    }

private:
    // Private constructor to prevent instantiation
    MemStack() {}

    // Disable copy constructor and assignment operator
    MemStack(const MemStack&) = delete;
    MemStack& operator=(const MemStack&) = delete;

    std::stack<std::string> stack_;
    mutable std::mutex mutex_;
};

#endif // MEMSTACK_H