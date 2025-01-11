#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include "cache.h"
#include "memory.h"

class Processor {
public:
    /**
     * Constructs a Processor object with a core ID, cache, and memory references.
     *
     * @param coreID - Unique identifier for the processor core.
     * @param cache - Reference to the cache system for this core.
     * @param memory - Reference to the main memory system.
     */
    Processor(int coreID, Cache& cache, Memory& memory);

    /**
     * Runs the processor, fetching and executing instructions.
     */
    void run();

    /**
     * Loads a list of instructions into the instruction queue.
     *
     * @param instructions - A vector of instruction strings to load.
     */
    void loadInstructions(const std::vector<std::string>& instructions);

private:
    int coreID;                      ///< Unique identifier for this processor core.
    Cache& cache;                    ///< Reference to the cache associated with this core.
    Memory& memory;                  ///< Reference to the main memory system.
    std::vector<std::string> instructionQueue; ///< Queue storing instructions for execution.

    /**
     * Fetches the next instruction from the instruction queue.
     *
     * @return The next instruction as a string.
     */
    std::string fetchInstruction();

    /**
     * Executes the given instruction.
     *
     * @param instruction - The instruction string to execute.
     */
    void executeInstruction(const std::string& instruction);
};

#endif // PROCESSOR_H
