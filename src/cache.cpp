#include "cache.h"
#include "node.h"

Cache::Cache(int size) : size(size), head(nullptr), cacheMap(std::unordered_map<std::string, Node*>()) {
    LOG(INFO) << "Cache initialized with size: " << size;
}

Cache::Cache() : size(0), head(nullptr), cacheMap(std::unordered_map<std::string, Node*>()) {
    LOG(INFO) << "Cache initialized with default size";
}


void Cache::setSize(int size) {
    this->size = size;
}

bool Cache::lookup(std::string address) const {
    try {
        cacheMap.at(address);
        return true;
    } catch (const std::out_of_range& e) {
        LOG(INFO) << "Nothing found in cache at address:  " << address;
    }
    return false;
}

std::string Cache::read(std::string address) {
    std::shared_lock<std::shared_mutex> lock(cacheMutex);

    Node* node = cacheMap[address];
    if (!node || node->data.empty()) {
        LOG(INFO) << "Node not found or empty at address: " << address << ". Removing node...";
        cacheMap.erase(address); 
        delete node;
        return "";
    }

    // If node is already head, return early
    if (node == head) return node->data;

    // Detach node from current position
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    // Attach at head
    node->prev = nullptr;
    node->next = head;
    if (head) head->prev = node;
    head = node;

    return node->data;
}

void Cache::insert(std::string address, const std::string& data) {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    if (cacheMap.size() >= size) {
        LOG(INFO) << "Cache is full. Removing least recently used node...";
        Node::removeFromEnd(head, cacheMap); 
    }

    if (lookup(address)) {
        LOG(INFO) << "Node already exists at address: " << address << ". Updating data...";
        update(address, data);
        return;
    }

    Node* newNode = new Node(address, data);
    cacheMap[address] = newNode;

    newNode->next = head;
    if (head) head->prev = newNode;
    head = newNode;
    LOG(INFO) << "Node inserted at address: " << address << " with data: " << data;
}

void Cache::update(std::string address, const std::string& data) {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    try {
        cacheMap.at(address);
        std::string oldData = cacheMap[address]->data;
        cacheMap[address]->data = data;
        LOG(INFO) << "Node updated at address: " << address << "\n. Old data: " << oldData << "\n. New data: " << data;
    } catch (const std::out_of_range& e) {
        LOG(INFO) << "Node not found at address: " << address << ". Inserting new node...";
        insert(address, data);
        return;
    }
}

void Cache::remove(std::string address) {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    try {
        cacheMap.at(address);
        Node* node = cacheMap[address];
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;
        cacheMap.erase(address);
        delete node;
        LOG(INFO) << "Node removed at address: " << address;
    } catch (const std::out_of_range& e) {
        LOG(INFO) << "Node not found at address: " << address;
    }
}

void Cache::display() const {
    Node* curr = head;
    while (curr) {
        LOG(INFO) << "Address: " << curr->address << " Data: " << curr->data;
        curr = curr->next;
    }
}
