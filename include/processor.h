#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <stack>
#include "cache.h"

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
        Processor(int coreID, int l1CacheSize, int l2CacheSize);

        void run();
        void loadInstructions(const std::vector<std::string>& instructions);

    private:
        int coreID;                      ///< Unique identifier for this processor core.
        int l1CacheSize;                 ///< Size of the L1 cache.
        int l2CacheSize;                 ///< Size of the L2 cache.
        Cache l1Cache;                  ///< Cache associated with this core.
        Cache l2Cache;                  ///< Cache associated with this core. (Will be shared per processor)               
        std::vector<std::string> instructionQueue; ///< Queue storing instructions for execution.
        std::stack<std::string> instructionStack; ///< Stack for executing instructions. (Will become a global singleton)

        /**
         * @brief Fetches the next instruction to be executed by the processor.
         * 
         * This method retrieves the next instruction from the instruction queue or memory.
         * It is typically used in the instruction fetch stage of the processor's pipeline.
         * 
         * @return std::string The next instruction as a string.
         */
        std::string fetchInstruction();

        /**
         * @brief Executes a given instruction on the processor.
         * 
         * This method takes a string representing an instruction and performs
         * the necessary operations to execute it on the processor.
         * 
         * @param instruction The instruction to be executed.
         */
        void executeInstruction(const std::string& instruction);
        
        /**
        * Handles the LOAD instruction by fetching data from the cache or memory.
        *
        * @param tokens - A vector of strings representing the instruction tokens.
        */
        void handleLoadInstruction(const std::vector<std::string>& tokens);

        /**
        * Handles the STORE instruction by storing data into the cache.
        *
        * @param tokens - A vector of strings representing the instruction tokens.
        */
        void handleStoreInstruction(const std::vector<std::string>& tokens);


        /**
         * @brief Handles the addition instruction for the processor.
         *
         * This function processes the addition instruction, performing the necessary
         * operations to add values as specified by the instruction set.
         */
        void handleAddInstruction();
};

#endif // PROCESSOR_H
