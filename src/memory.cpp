#include "memory.h"

#include "easylogging++.h"

Memory::Memory() : memory() {
    LOG(INFO) << "Memory initialized.";
}


std::string Memory::get(std::string &key) {
    std::shared_lock<std::shared_mutex> lock(mutex_); // Shared lock for reading
    if (!contains(key)) {
        throw std::invalid_argument("Key not found in memory");
    }
    Node* node = memory[key];
    return node->data;
}

void Memory::insert(std::string &key, Node* value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    memory[key] = value;
}

void Memory::update(std::string &key, Node* value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    memory[key] = value;
}

void Memory::remove(std::string &key) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    memory.erase(key);
}

size_t Memory::size() {
    std::shared_lock<std::shared_mutex> lock(mutex_); 
    return memory.size();
}

bool Memory::contains(std::string &key) {
    std::shared_lock<std::shared_mutex> lock(mutex_); 
    return memory.count(key) > 0;
}
