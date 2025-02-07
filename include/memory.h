#ifndef MEMORY_H
#define MEMORY_H

#include <unordered_map>
#include <shared_mutex>
#include <string>
#include "node.h"

class Memory {

    private:
    std::unordered_map<std::string, Node*> memory;
    mutable std::shared_mutex mutex_;

    public:
    Memory();

    std::string get(std::string& key);
    void insert(std::string& key, Node* value);
    void update(std::string& key, Node* value);
    void remove(std::string& key);
    size_t size();
    bool contains(std::string& key);
    
};
#endif // MEMORY_H