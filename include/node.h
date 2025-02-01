#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <string>
#include <unordered_map>

class Node {
    public:
    std::string address;  // Store the address associated with the node
    std::string data;
    Node* prev;
    Node* next;

    Node(const std::string& addr, const std::string& d);

    static void removeFromEnd(Node*& head, std::unordered_map<std::string, Node*>& cacheMap);
        
};

#endif // NODE_H