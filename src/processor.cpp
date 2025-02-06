#include "processor.h"
#include <iostream>
#include "easylogging++.h"
#include "INSTRUCTION_ENUM.h"

Processor::Processor(int coreID, int l1CacheSize, int l2CacheSize)
    : coreID(coreID), l1Cache(Cache(l1CacheSize)), l2Cache(Cache(l2CacheSize)) {
    LOG(INFO) << "Processor " << coreID << " initialized with L1 cache size: " << l1CacheSize
              << " and L2 cache size: " << l2CacheSize;
}

void Processor::loadInstructions(const std::vector<std::string>& instructions) {
    instructionQueue = instructions;
}

void Processor::run() {
    LOG(INFO) << "Processor " << coreID << " is running...";

    while (!instructionQueue.empty()) {
        std::string instruction = fetchInstruction();
        executeInstruction(instruction);
    }

    LOG(INFO) << "Processor " << coreID << " has finished executing all instructions.";
    LOG(INFO) << "Displaying cache and memory states...";
    l1Cache.display();
    l2Cache.display();
}


std::string Processor::fetchInstruction() {
    std::string instruction = instructionQueue.front();
    instructionQueue.erase(instructionQueue.begin());
    return instruction;
}

void Processor::executeInstruction(const std::string& instruction) {
    LOG(INFO) << "Processor " << coreID << " executing instruction: " << instruction;

    std::istringstream iss(instruction);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    InstructionEnum operation = stringToInstruction(tokens[0]);

    switch (operation) {
        case LOAD:
            handleLoadInstruction(tokens);
            break;
        case STORE:
            handleStoreInstruction(tokens);
            break;
        case ADD:
            handleAddInstruction();
            LOG(INFO) << "ADD operation";
            break;
        case INVALID:
            LOG(WARNING) << "Invalid instruction: " << instruction;
            break;
        default:
            LOG(ERROR) << "Unknown instruction: " << operation << " " << instruction; 
            break;
    }
}

void Processor::handleLoadInstruction(const std::vector<std::string>& tokens) {
    LOG(INFO) << "LOAD operation";
    if (tokens.size() < 2) {
        LOG(ERROR) << "Invalid LOAD instruction, missing address";
        return;
    }
    std::string address = tokens[1];

    if (address.empty()) {
        LOG(ERROR) << "Invalid LOAD instruction, missing address";
        return;
    }

    if (address.find(' ') != std::string::npos) {
        address = address.substr(0, address.find(' '));
    }

    if (l1Cache.lookup(address)) {
        LOG(INFO) << "l1Cache hit for address: " << address;
        instructionStack.push(l1Cache.read(address));
    } else if (l2Cache.lookup(address)) {
        LOG(INFO) << "l1Cache miss for address: " << address;
        LOG(INFO) << "l2Cache hit for address: " << address;
        instructionStack.push(l2Cache.read(address));
    } else {
        LOG(INFO) << "Memory miss for address: " << address;
    }
}

void Processor::handleStoreInstruction(const std::vector<std::string>& tokens) {
    LOG(INFO) << "STORE operation";
    if (tokens.size() < 3) {
        LOG(ERROR) << "Invalid STORE instruction, missing address or data";
        return;
    }

    std::string address = tokens[1];
    std::string data = tokens[2];

    if (address.empty() || data.empty()) {
        LOG(ERROR) << "Invalid STORE instruction, missing address or data"; 
        return;
    }
    LOG(INFO) << "Storing data in l1Cache for address: " << address;
    l1Cache.insert(address, data);
    LOG(INFO) << "Data stored in l1Cache for address: " << address;
}

void Processor::handleAddInstruction() {
    if (instructionStack.size() < 2) {
        LOG(ERROR) << "ADD operation requires at least two operands";
        return;
    }

    std::string operand1 = instructionStack.top();
    instructionStack.pop();
    std::string operand2 = instructionStack.top();
    instructionStack.pop();

    int result = std::stoi(operand1) + std::stoi(operand2);
    instructionStack.push(std::to_string(result));
}
