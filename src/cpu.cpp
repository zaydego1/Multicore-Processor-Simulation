#include "cpu.h"
#include "processor.h"

CPU::CPU(int numOfProcessors, int numOfCores, int l1CacheSize, int l2CacheSize) :
    numOfProcessors(numOfProcessors), numOfCores(numOfCores), 
    l1CacheSize(l1CacheSize), l2CacheSize(l2CacheSize) {
}

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
        processor.second->run();
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
    processors = std::unordered_map<int, std::unique_ptr<Processor>>();
    for (int i = 1; i <= numOfProcessors; ++i) {
        LOG(INFO) << "Initializing processor " << i;
        Processor processor = Processor(i, numOfCores, l1CacheSize, l2CacheSize);
        processors.insert({i, std::unique_ptr<Processor>(&processor)});
    }
}