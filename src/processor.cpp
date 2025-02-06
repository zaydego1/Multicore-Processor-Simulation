#include "processor.h"

Processor::Processor(int processorId, int numOfCores, int l1CacheSize, int l2CacheSize)
    : processorId(processorId), numOfCores(numOfCores), l2Cache(Cache(l2CacheSize)) {
    LOG(INFO) << "Processor " << processorId << " initialized";
}

void Processor::run() {
    LOG(INFO) << "Processor " << processorId << " is running...";
    InstructionQueue& instructionQueue = InstructionQueue::getInstance();
    while (!instructionQueue.isEmpty()) {
        std::string instruction = fetchInstruction();
        scheduleInstruction(instruction, 1);
    }
}

void Processor::initializeCores(int numOfCores, int l1CacheSize, Cache& l2Cache) {
    std::unordered_map<int, Core> cores = std::unordered_map<int, Core>();
    for (int i = 1; i <= numOfCores; i++) {
        Core core(i, l1CacheSize, l2Cache);
        cores.insert({i, core});
    }
}

std::string Processor::fetchInstruction() {
    InstructionQueue& instructionQueue = InstructionQueue::getInstance();
    std::string instruction = instructionQueue.peek();
    instructionQueue.dequeue();
    return instruction;
}

void Processor::scheduleInstruction(const std::string& instruction, int retryCount) {
    if (instruction.empty() || retryCount > 5) {
        return;
    }
    for (auto& core : cores) {
        if (core.second.isReady()) {
            core.second.executeInstruction(instruction);
            return;
        }
}   LOG(INFO) << "No cores available to execute instruction: " << instruction << "retrying: Attempt: " << retryCount;
    scheduleInstruction(instruction, retryCount + 1);
}
