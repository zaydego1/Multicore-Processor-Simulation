#include "processor.h"

Processor::Processor(int& processorId, int& numOfCores, int& l1CacheSize, int& l2CacheSize):
    processorId(processorId),
    numOfCores(numOfCores),
    l1CacheSize(l1CacheSize),
    l2CacheSize(l2CacheSize),
    l2Cache(Cache(l2CacheSize)) {
    LOG(INFO) << "Processor " << processorId << " initialized";
}

void Processor::run() {
    LOG(INFO) << "Processor " << processorId << " is running...";
    initializeCores(numOfCores, l1CacheSize, l2Cache);
    InstructionQueue& instructionQueue = InstructionQueue::getInstance();
    LOG(INFO) << "Processor " << processorId << " is fetching and executing instructions...";
    while (!instructionQueue.isEmpty()) {
        std::string instruction = fetchInstruction();
        scheduleInstruction(instruction, 1);
    }
}

void Processor::initializeCores(const int& numOfCores, const int& l1CacheSize, Cache& l2Cache) {

    LOG(INFO) << "Initializing cores for processor " << processorId;
    for (int i = 0; i < numOfCores; i++) {
        LOG(INFO) << "Initializing core " << i;
        Core core = Core(i, l1CacheSize, l2Cache);
        Core* corePtr = &core;
        cores.push_back(corePtr);
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
        LOG(INFO) << "Instruction is empty or retry count exceeded, skipping instruction";
        return;
    }

    for (auto& core : cores) {
        LOG(INFO) << "Attempting to schedule instruction: " << instruction << " on core: " << core->coreId;
        if (core->isReady()) {
            core->executeInstruction(instruction);
            return;
        }
}   LOG(INFO) << "No cores available to execute instruction: " << instruction << " retrying: Attempt: " << retryCount;
    scheduleInstruction(instruction, retryCount + 1);
}
