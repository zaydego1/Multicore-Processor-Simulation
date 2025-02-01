#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <stack>
#include "cache.h"

class Processor {
    public:
        Processor(int coreID, int l1CacheSize, int l2CacheSize);

        void run();
        void loadInstructions(const std::vector<std::string>& instructions);

    private:
        int coreID;                      ///< Unique identifier for this processor core.
        int l1CacheSize;                 ///< Size of the L1 cache.
        int l2CacheSize;                 ///< Size of the L2 cache.
        Cache l1Cache;
        Cache l2Cache;                  ///< Reference to the cache associated with this core.               
        std::vector<std::string> instructionQueue; ///< Queue storing instructions for execution.
        std::stack<std::string> instructionStack; ///< Stack for executing instructions.

        std::string fetchInstruction();
        void executeInstruction(const std::string& instruction);
};

#endif // PROCESSOR_H
