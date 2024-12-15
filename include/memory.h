#ifndef MEMORY_H
#define MEMORY_H

#include <unordered_map>
#include <string>

class Memory{

    public:
        //memory operations 
        std::string read(int address);
        void write (int address,const std:: string& address);
        void displayMemoryState() const;
    private:
        std::unordered_map<int,std::string> memory;
}
#ifndef // MEMORY_H