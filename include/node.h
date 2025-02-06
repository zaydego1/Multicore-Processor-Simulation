#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <string>
#include <unordered_map>

/**
 * @class Node
 * @brief Represents a node in a doubly linked list.
 *
 * The Node class is used to store data, data addresses and maintain links to the previous and next nodes
 * in a doubly linked list. It also includes a static method to remove a node from the end
 * of the list.
 */
class Node {
    public:
    std::string address;  // Store the address associated with the node
    std::string data;   // Store the data associated with the node
    Node* prev; // Pointer to the previous node in the list
    Node* next; // Pointer to the next node in the list

    /**
     * @brief Constructs a new Node object.
     * 
     * @param addr The address of the node.
     * @param d The data associated with the node.
     */
    Node(const std::string& addr, const std::string& d);

    /**
     * @brief Removes the last node from the linked list and updates the cache map.
     * 
     * This function removes the node at the end of the linked list pointed to by `head`.
     * It also updates the provided cache map to reflect the removal of the node.
     * 
     * @param head A reference to the pointer to the head of the linked list.
     * @param cacheMap A reference to an unordered map that caches nodes by their string keys.
     */
    static void removeFromEnd(Node*& head, std::unordered_map<std::string, Node*>& cacheMap);
        
};

#endif // NODE_H