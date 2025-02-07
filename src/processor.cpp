#include "processor.h"

Processor::Processor(int pId, int numCores, int l1, int l2, Memory& memory) :
processorId(pId), numOfCores(numCores), l1CacheSize(l1), l2CacheSize(l2), l2Cache(Cache(l2)), memory(memory) {
    LOG(INFO) << "Processor " << processorId << " initialized with " << numOfCores << " cores, L1 cache size: " << l1CacheSize << " and L2 cache size: " << l2CacheSize;
}

void Processor::run() {
    LOG(INFO) << "Processor " << processorId << " is running...";
    initializeCores();
    InstructionQueue& instructionQueue = InstructionQueue::getInstance();
    LOG(INFO) << "Processor " << processorId << " is fetching and executing instructions...";
    while (!instructionQueue.isEmpty()) {
        std::string instruction = fetchInstruction();
        scheduleInstruction(instruction, 1);
    }
}

void Processor::initializeCores() {
    LOG(INFO) << "Initializing cores for processor " << processorId;
    for (int i = 1; i <= numOfCores; i++) {
        LOG(INFO) << "Initializing core " << i;
        cores.insert({i, std::shared_ptr<Core>(new Core(i, l1CacheSize, l2Cache, memory))});
    }
}

Cache& Processor::getL2Cache() {
    return this->l2Cache;
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
        std::shared_ptr<Core> corePtr = core.second;
        LOG(INFO) << "Checking if core " << corePtr->isReady() << " is ready to execute instruction: " << instruction;
        if (corePtr->isReady()) {
            corePtr->executeInstruction(instruction);
            return;
        }
}   LOG(INFO) << "No cores available to execute instruction: " << instruction << " retrying: Attempt: " << retryCount;
    scheduleInstruction(instruction, retryCount + 1);
}
