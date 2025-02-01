#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <vector>
#include <string>
#include "node.h"

class Cache {

    public:
        //Cache configuration 
        Cache(int size);
        ~Cache();

        //cache operations
        bool lookup(std::string address) const;
        std::string read(std::string address);
        void insert(std::string address, const std::string& data);
        void update (std::string address, const std::string& data);
        void display() const;


    private:
        int size;
        Node* head;
        std::unordered_map<std::string, Node*> cacheMap;

};

#endif //CACHE_H