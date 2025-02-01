#include <iostream>
#include <node.h>
#include "easylogging++.h"

Node::Node(const std::string& addr, const std::string& d)
: data(data), address(address), prev(nullptr), next(nullptr) {}

void Node::removeFromEnd(Node*& head, std::unordered_map<std::string, Node*>& cacheMap) {
    if (!head) return;
    Node* curr = head;
    while (curr->next) curr = curr->next;  // Find LRU node

    cacheMap.erase(curr->address);  // Remove from map
    if (curr->prev) 
        curr->prev->next = nullptr;
    else 
        head = nullptr;  // Last node was head

    delete curr;
}