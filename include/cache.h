#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <vector>
#include <string>

class Cache {

    public:
        //Cache configuration 
        Cache(int size, int lineSize, int associativity);

        //cache operations
        bool lookup(int address);
        void update (int address, const std::string& data);
        void displayCacheState() const;


    private:

        struct CacheLine{
            int tag;
            bool valid;
            std::string data;
        }

        int size;
        int lineSize;
        int associativity;
        std::vector<std::vector<CacheLine> CacheLines;

        //helper function
        int getTag(int address) const;
        int getIndex(int addresss) const;
        int getOffset(int address) const;
        void replaceLine(int index, int tag, const std::string& data);

}

#endif //CACHE_H