#ifndef CPU_H
#define CPU_H

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <chrono>
#include <iostream>
#include <memory>

#include "processor.h"
#include "cache.h"
#include "core.h"
#include "instructionQueue.h"
#include "easylogging++.h"
#include "memory.h"

class CPU {
public:
    CPU(int numOfProcessors, int numOfCores, int l1CacheSize, int l2CacheSize, Memory& memory); 

    std::unordered_map<int, std::shared_ptr<Processor>> processors;

    void run();
    void loadInstructionQueue(std::vector<std::string>& instructions);


private:
    int l1CacheSize;  // Size of the L1 cache
    int l2CacheSize;  // Size of the L2 cache
    int numOfCores;  // Number of cores in each processor
    int numOfProcessors;  // Number of processors in the system
    Memory& memory;
    void initializeProcessors();
};

#endif // CPU_H