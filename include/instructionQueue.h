#ifndef INSTRUCTIONQUEUE_H
#define INSTRUCTIONQUEUE_H

#include <vector>
#include <string>
#include <mutex>

class InstructionQueue {
public:
    static InstructionQueue& getInstance() {
        static InstructionQueue instance;
        return instance;
    }

    void enqueue(const std::string& instruction) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push_back(instruction);
    }

    std::string dequeue() {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return "";
        }
        std::string instruction = queue.front();
        queue.erase(queue.begin());
        return instruction;
    }

    // Check if the queue is empty
    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    // Peek at the front of the queue without removing it
    std::string peek() {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return "";
        }
        return queue.front();
    }
    
    // Get the size of the queue
    size_t size() {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }

private:
    // Private constructor to prevent instantiation
    InstructionQueue() = default;

    // Delete copy constructor and assignment operator
    InstructionQueue(const InstructionQueue&) = delete;
    InstructionQueue& operator=(const InstructionQueue&) = delete;

    std::vector<std::string> queue;
    std::mutex mtx;
};
#endif // INSTRUCTIONQUEUE_H