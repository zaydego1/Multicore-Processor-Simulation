#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

#include "cache.h"
#include "core.h"
#include "instructionQueue.h"
#include "easylogging++.h"
#include "INSTRUCTION_ENUM.h"
#include "memory.h"

class Processor {
    public:
        Processor(int processorId, int numOfCores, int l1CacheSize, int l2CacheSize, Memory& memory);

        int processorId;

        void run();
        std::string fetchInstruction();

    private:
        int numOfCores;                          
        int l1CacheSize;                
        int l2CacheSize;                 
        Cache* l2Cache;                 
        Memory& memory;         
        std::unordered_map<int, std::shared_ptr<Core>> cores;

        void scheduleInstruction(const std::string& instruction, int retryCount);
        void initializeCores();
};

#endif // PROCESSOR_H
