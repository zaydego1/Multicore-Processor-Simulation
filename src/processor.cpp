#include "processor.h"
#include <iostream>

/**
 * Constructs a Processor object with a core ID, cache, and memory references.
 *
 * @param coreID - Unique identifier for the processor core.
 * @param cache - Reference to the cache system for this core.
 * @param memory - Reference to the main memory system.
 */
Processor::Processor(int coreID, Cache& cache, Memory& memory)
    : coreID(coreID), cache(cache), memory(memory) {}

/**
 * Loads a list of instructions into the instruction queue.
 *
 * @param instructions - A vector of instruction strings to load.
 */
void Processor::loadInstructions(const std::vector<std::string>& instructions) {
    instructionQueue = instructions;
}

/**
 * Runs the processor by fetching and executing instructions until the queue is empty.
 */
void Processor::run() {
    std::cout << "Processor " << coreID << " starting execution.\n";

    while (!instructionQueue.empty()) {
        std::string instruction = fetchInstruction();
        executeInstruction(instruction);
    }

    std::cout << "Processor " << coreID << " has finished execution.\n";
}

/**
 * Fetches the next instruction from the front of the instruction queue.
 *
 * @return The fetched instruction as a string.
 */
std::string Processor::fetchInstruction() {
    std::string instruction = instructionQueue.front();
    instructionQueue.erase(instructionQueue.begin());
    return instruction;
}

/**
 * Executes the given instruction, handling basic LOAD and STORE operations.
 *
 * @param instruction - The instruction string to execute.
 */
void Processor::executeInstruction(const std::string& instruction) {
    std::cout << "Processor " << coreID << " executing instruction: " << instruction << "\n";

    if (instruction.find("LOAD") == 0) {
        // Extract the memory address from the instruction
        std::string address = instruction.substr(5);

        // Read data from the cache at the specified address
        int data = cache.readData(address);
        std::cout << "Loaded data: " << data << " from address " << address << "\n";
    } 
    else if (instruction.find("STORE") == 0) {
        // Extract the memory address from the instruction
        std::string address = instruction.substr(6);

        // Example data to store: use core ID multiplied by 100
        int value = coreID * 100;

        // Write data to the cache at the specified address
        cache.writeData(address, value);
        std::cout << "Stored data: " << value << " to address " << address << "\n";
    } 
    else {
        std::cout << "Unknown instruction: " << instruction << "\n";
    }
}
