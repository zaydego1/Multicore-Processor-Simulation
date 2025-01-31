#ifndef MEMORY_H
#define MEMORY_H

#include <unordered_map>
#include <string>

class Memory {

    public:
        //memory operations 
        std::string read(std::string address);
        void write (std::string address,const std:: string& address);
        void displayMemoryState() const;
    private:
        std::unordered_map<std::string, std::string> memory;
}
#endif // MEMORY_H