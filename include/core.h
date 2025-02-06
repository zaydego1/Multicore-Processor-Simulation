#ifndef CORE_H
#define CORE_H

#include <iostream>
#include "core.h"
#include "easylogging++.h"
#include "INSTRUCTION_ENUM.h"

#include "memStack.h"
#include "cache.h"
#include "instructionQueue.h"

class Core
{
public:
    Core(int coreId, int l1CacheSize, Cache &l2Cache);

    bool isReady();
    void executeInstruction(const std::string &instruction);

private:
    bool readyForInstruction;
    int coreId;
    Cache l1Cache;
    Cache &l2Cache;

    /**
     * Handles the LOAD instruction by fetching data from the
cache or memory.
     *
     * @param tokens - A vector of strings representing the
instruction tokens.
     */
    void handleLoadInstruction(const std::vector<std::string> &
                                   tokens);

    /**
     * Handles the STORE instruction by storing data into the
cache.
     *
     * @param tokens - A vector of strings representing the
instruction tokens.
     */
    void handleStoreInstruction(const std::vector<std::string> &
                                    tokens);

    /**
     * @brief Handles the addition instruction for the processor.
     *
     * This function processes the addition instruction,
performing the necessary
     * operations to add values as specified by the instruction
set.
     */
    void handleAddInstruction();
};

#endif // CORE_H