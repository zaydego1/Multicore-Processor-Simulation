#ifndef CORE_H
#define CORE_H

#include <iostream>
#include "core.h"
#include "easylogging++.h"
#include "INSTRUCTION_ENUM.h"

#include "memStack.h"
#include "cache.h"
#include "instructionQueue.h"
#include "memory.h"

class Core{
public:
    Core(int id, int l1, Cache* l2, Memory& memory);
    int coreId;

    bool isReady();
    void executeInstruction(const std::string &instruction);
    void displayCacheState() const;

private:
    bool readyForInstruction;
    int l1CacheSize;
    Cache* l2Cache;
    Cache l1Cache;
    Memory& memory;

    void handleLoadInstruction(const std::vector<std::string> &tokens);
    void handleStoreInstruction(const std::vector<std::string> &tokens);
    void handleAddInstruction(const std::vector<std::string> &tokens);
};

#endif // CORE_H