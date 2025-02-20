#include "cpu.h"

CPU::CPU(int numOfProcessors, int numOfCores, int l1CacheSize, int l2CacheSize, Memory& memory) :
    numOfProcessors(numOfProcessors), numOfCores(numOfCores), l1CacheSize(l1CacheSize), l2CacheSize(l2CacheSize), memory(memory) {}

void CPU::run() {
    LOG(INFO) << "CPU is running...";
    LOG(INFO) << "Number of processors: " << numOfProcessors;
    LOG(INFO) << "Number of cores per processor: " << numOfCores;
    LOG(INFO) << "L1 cache size: " << l1CacheSize;
    LOG(INFO) << "L2 cache size: " << l2CacheSize;
    LOG(INFO) << "Initializing memory, instruction queue, memory stack, and processors...";
    auto start = std::chrono::high_resolution_clock::now();
    initializeProcessors();

    for (auto& processor : processors) {
        std::shared_ptr<Processor> processorPtr = processor.second;
        processorPtr->run();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    LOG(INFO) << "CPU has finished executing all instructions in " << elapsed.count() << " seconds.";

}

void CPU::loadInstructionQueue(std::vector<std::string>& instructions) {
    InstructionQueue& instructionQueue = InstructionQueue::getInstance();
    while (!instructions.empty()) {
        instructionQueue.enqueue(instructions.front());
        instructions.erase(instructions.begin());
    }
}

void CPU::initializeProcessors() {
    for (int i = 1; i <= numOfProcessors; ++i) {
        LOG(INFO) << "Initializing processor " << i;
        processors.insert({i, std::shared_ptr<Processor>(new Processor(i, numOfCores, l1CacheSize, l2CacheSize, memory))});
    }
}