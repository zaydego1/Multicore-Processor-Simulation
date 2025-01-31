#include "processor.h"
#include <iostream>
#include "easylogging++.h"
#include "INSTRUCTION_ENUM.h"

/**
 * Constructs a Processor object with a core ID, cache sizes, and memory references.
 *
 * @param coreID - Unique identifier for the processor core.
 * @param l1CacheSize - Size of the L1 cache.
 * @param l2CacheSize - Size of the L2 cache.
 */
Processor::Processor(int coreID, int l1CacheSize, int l2CacheSize)
    : coreID(coreID), l1Cache(Cache(l1CacheSize)), l2Cache(Cache(l2CacheSize)) {
    LOG(INFO) << "Processor " << coreID << " initialized with L1 cache size: " << l1CacheSize
              << " and L2 cache size: " << l2CacheSize << "\n";
}

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
    LOG(INFO) << "Processor " << coreID << " is running...\n";

    while (!instructionQueue.empty()) {
        std::string instruction = fetchInstruction();
        executeInstruction(instruction);
    }

    LOG(INFO) << "Processor " << coreID << " has finished executing all instructions.\n";
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
    LOG(INFO) << "Processor " << coreID << " executing instruction: " << instruction;

    std::istringstream iss(instruction);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    InstructionEnum operation = stringToInstruction(tokens[0]);
    std::string address;
    std::string data;

    switch (operation) {
        case LOAD:
            LOG(INFO) << "LOAD operation\n";
            if (tokens.size() < 2) {
                LOG(ERROR) << "Invalid LOAD instruction, missing address: " << instruction << "\n";
                break;
            }
            address = tokens[1];

            if (address.empty()) {
                LOG(ERROR) << "Invalid LOAD instruction, missing address: " << instruction << "\n";
                break;
            }

            if (address.find(' ') != std::string::npos) {
                address = address.substr(0, address.find(' '));
            }
            
            if (l1Cache.lookup(address)) {
                LOG(INFO) << "l1Cache hit for address: " << address << "\n";
                instructionStack.push(l1Cache.read(address));
            } else if (l2Cache.lookup(address)) {
                LOG(INFO) << "l1Cache miss for address: " << address << "\n";
                LOG(INFO) << "l2Cache hit for address: " << address << "\n";
                instructionStack.push(l2Cache.read(address));
            }
            // else if (memory.lookup(address)) {
            //     LOG(INFO) << "l2Cache miss for address: " << address << "\n";
            //     LOG(INFO) << "Memory hit for address: " << address << "\n";
            //     instructionStack.push(memory.read(address));
            // }
            else {
                LOG(INFO) << "Memory miss for address: " << address << "\n";
            }
            break;
        case STORE:
            LOG(INFO) << "STORE operation\n";
            if (tokens.size() < 3) {
                LOG(ERROR) << "Invalid STORE instruction, missing address or data: " << instruction << "\n";
                break;
            }

            address = tokens[1];
            data = tokens[2];

            if (address.empty() || data.empty()) {
                LOG(ERROR) << "Invalid STORE instruction, missing address or data: " << instruction << " " << address << " " << data << "\n"; 
                break;
            }
            LOG(INFO) << "Storing data in l1Cache for address: " << address << "\n";
            l1Cache.insert(address, data);
            LOG(INFO) << "Data stored in l1Cache for address: " << address << "\n";
            break;
        case INVALID:
            LOG(ERROR) << "Invalid instruction: " << instruction;
            break;
        default:
            LOG(WARNING) << "Unknown instruction: " << operation << " " << instruction << "\n"; 
            break;
    }
}
