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
        Processor(int processorId, int numOfCores, int l1CacheSize, int l2CacheSize);

        int processorId;

        void run();
        std::string fetchInstruction();
        Cache& getL2Cache();

    private:
        int numOfCores;                            ///< Unique identifier for this processor core.
        int l1CacheSize;                 ///< Size of the L1 cache.
        int l2CacheSize;                 ///< Size of the L2 cache.
        Cache l2Cache;                  ///< Cache associated with this core. (Will be shared per processor)           
        std::unordered_map<int, std::shared_ptr<Core>> cores;

        void scheduleInstruction(const std::string& instruction, int retryCount);
        void initializeCores();
};

#endif // PROCESSOR_H
