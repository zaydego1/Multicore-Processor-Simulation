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

/**
 * @class Processor
 * @brief Represents a processor core with its own caches and instruction handling capabilities.
 *
 * The Processor class simulates a processor core with L1 and L2 caches. It can load and execute
 * instructions, and handle specific instructions like LOAD and STORE.
 *
 * @note This class assumes the existence of a Cache class for managing cache operations.
 */
class Processor {
    public:
        Processor(int& processorId, int& numOfCores, int& l1CacheSize, int& l2CacheSize);

        const int& processorId;
        void run();
        std::string fetchInstruction();                      ///< Unique identifier for this processor core.

    private:
        const int& numOfCores;                            ///< Unique identifier for this processor core.
        const int& l1CacheSize;                 ///< Size of the L1 cache.
        const int& l2CacheSize;                 ///< Size of the L2 cache.
        Cache l2Cache;                  ///< Cache associated with this core. (Will be shared per processor)
        std::vector<Core*> cores;        ///< Vector of cores in the processor.               


        void scheduleInstruction(const std::string& instruction, int retryCount);
        void initializeCores(const int& numOfCores, const int& l1CacheSize, Cache& l2Cache);
};

#endif // PROCESSOR_H
