#define ELPP_IMPLEMENTATION 
#include "easylogging++.h"
#include "memory.h"
#include "cpu.h"
#include "memStack.h"

INITIALIZE_EASYLOGGINGPP  // Macro to initialize the logger

int main() {
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime %level %msg");
    el::Loggers::reconfigureLogger("default", defaultConf);


    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
    el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
    el::Configurations fileConf;
    fileConf.setToDefault();
    fileConf.set(el::Level::Global, el::ConfigurationType::Filename, "logging/MulticoreProcessorSimulation.log");
    el::Loggers::reconfigureLogger("default", fileConf);

    LOG(INFO) << "Welcome to the Multicore Processor Simulation!";
    LOG(INFO) << "This program simulates a multicore processor system with multiple caches and a shared memory system.";
    LOG(INFO) << "The program reads a list of instructions and executes them on the processor cores.";
    LOG(INFO) << "The cache system is used to store frequently accessed data, and the memory system is used to store the rest.";
    LOG(INFO) << "The program outputs the cache and memory states after each instruction execution.";

    LOG(INFO) << "Initializing processor simulation... ";
    Memory memory = Memory();
    int processors = 2;
    int cores = 4;
    int l1CacheSize = 10;
    int l2CacheSize = 20;
    CPU cpu(processors, cores, l1CacheSize, l2CacheSize, memory);
    LOG(INFO) << "Processor simulation initialized.";

    std::vector<std::string> instructions = {
        "STORE 0x1000 7",
        "LOAD 0x1000",
        "STORE 0x2000 8",
        "LOAD 0x2000",
        "STORE 0x3000 9",
        "LOAD 0x3000",
        "STORE 0x4000 0",
        "LOAD 0x4000",
        "STORE 0x5000 10",
        "LOAD 0x5000",
        "DIV 0x6000",
        "LOAD 0x6000"
    };

    cpu.loadInstructionQueue(instructions);
    cpu.run();
    LOG(INFO) << MemStack::getInstance().top();

    return 0;
}