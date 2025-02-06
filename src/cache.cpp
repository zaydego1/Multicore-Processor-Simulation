#include "cache.h"
#include "node.h"

Cache::Cache(int size) : size(size), head(nullptr), cacheMap(std::unordered_map<std::string, Node*>()) {
    LOG(INFO) << "Cache initialized with size: " << size << "\n";
}

Cache::~Cache() {
    Node* curr = head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    cacheMap.clear();
}

bool Cache::lookup(std::string address) const {
    try {
        cacheMap.at(address);
        return true;
    } catch (const std::out_of_range& e) {
        LOG(INFO) << "Cache miss at address: " << address;
    }
    return false;
}


std::string Cache::read(std::string address) {
    if (!lookup(address)) return "";

    Node* node = cacheMap[address];
    if (!node || node->data.empty()) {
        cacheMap.erase(address);  // Remove invalid entry
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
    if (cacheMap.size() >= size) {
        Node::removeFromEnd(head, cacheMap); 
    } // Evict before inserting

    Node* newNode = new Node(address, data);
    cacheMap[address] = newNode;

    newNode->next = head;
    if (head) head->prev = newNode;
    head = newNode;
}

void Cache::update(std::string address, const std::string& data) {
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

void Cache::display() const {
    LOG(INFO) << "Cache state (MRU to LRU):";
    Node* curr = head;
    while (curr) {
        LOG(INFO) << "Address: " << curr->address << " Data: " << curr->data;
        curr = curr->next;
    }
}
