#include "core.h"

Core::Core(int id, int l1, Cache* l2, Memory& memory) 
    : coreId(id), l1CacheSize(l1), l1Cache(l1CacheSize), l2Cache(l2), readyForInstruction(true), memory(memory) {}

bool Core::isReady() {
    return readyForInstruction;
}

void Core::executeInstruction(const std::string& instruction) {
    LOG(INFO) << "Core " << coreId << " executing instruction: " << instruction;

    std::istringstream iss(instruction);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    InstructionEnum operation = stringToInstruction(tokens[0]);

    switch (operation) {
        case LOAD:
            handleLoadInstruction(tokens);
            readyForInstruction = true;
            break;
        case STORE:
            handleStoreInstruction(tokens);
            readyForInstruction = true;
            break;
        case ADD:
            LOG(INFO) << "ADD operation";
            handleAddInstruction(tokens);
            readyForInstruction = true;
            break;
        case INVALID:
            LOG(WARNING) << "Invalid instruction: " << instruction;
            readyForInstruction = true;
            break;
        default:
            LOG(ERROR) << "Unknown instruction: " << operation << " " << instruction; 
            readyForInstruction = true;
            break;

    }
}

void Core::handleLoadInstruction(const std::vector<std::string>& tokens) {
    MemStack& memStack = MemStack::getInstance();
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
        memStack.push(l1Cache.read(address));
    } else if (l2Cache->lookup(address)) {
        LOG(INFO) << "l2Cache hit for address: " << address;
        l1Cache.insert(address, l2Cache->read(address));
        l2Cache->remove(address);
        memStack.push(l2Cache->read(address));
    } else if (memory.contains(address)) {
        LOG(INFO) << "Memory hit for address: " << address;
        l1Cache.insert(address, memory.get(address));
        memStack.push(l2Cache->read(address));
    } else {
        LOG(INFO) << "l1Cache miss for address: " << address;
        LOG(INFO) << "l2Cache miss for address: " << address;
        LOG(INFO) << "Memory miss for address: " << address;
        LOG(INFO) << "Data not found for address: " << address;
    }
}

void Core::handleStoreInstruction(const std::vector<std::string>& tokens) {
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
    memory.insert(address, new Node(address, data));
    LOG(INFO) << "Data stored in l1Cache for address: " << address;
    LOG(INFO) << "Data stored in memory for address: " << address;
}

void Core::handleAddInstruction(const std::vector<std::string>& tokens) {
    MemStack& memStack = MemStack::getInstance();
    if (memStack.size() < 2) {
        LOG(ERROR) << "ADD operation requires at least two operands";
        return;
    }

    if (tokens.size() < 2) {
        LOG(ERROR) << "Invalid ADD instruction, missing memory address";
        return;
    }

    std::string address = tokens[1];
    std::string operand1 = memStack.pop();
    std::string operand2 = memStack.pop();

    try {
        int result = std::stoi(operand1) + std::stoi(operand2);
        LOG(INFO) << "ADD operation result: " << result;
        l1Cache.insert(address, std::to_string(result));
        memory.insert(address, new Node(address, std::to_string(result)));
        memStack.push(std::to_string(result));
    } catch (const std::invalid_argument& e) {
        LOG(ERROR) << "Invalid argument for ADD operation: " << e.what();
    } catch (const std::out_of_range& e) {
        LOG(ERROR) << "Out of range error for ADD operation: " << e.what();
    }
}

void Core::displayCacheState() const {
    LOG(INFO) << "Displaying cache state for Core " << coreId;
    LOG(INFO) << "L1 Cache:";
    l1Cache.display();
    LOG(INFO) << "L2 Cache:";
    l2Cache->display();
}



