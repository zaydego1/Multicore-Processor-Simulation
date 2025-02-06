#include "core.h"

Core::Core(int coreId, int l1CacheSize, Cache& l2Cache) 
    : coreId(coreId), l1Cache(Cache(l1CacheSize)), l2Cache(l2Cache), readyForInstruction(true) {
    LOG(INFO) << "Core " << coreId << " initialized";
}

bool Core::isReady() {
    return readyForInstruction;
}

void Core::executeInstruction(const std::string& instruction) {
    readyForInstruction = false;
    LOG(INFO) << "Core " << coreId << " executing instruction: " << instruction;

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

        readyForInstruction = true;
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
        memStack.push(address);
    } else if (l2Cache.lookup(address)) {
        LOG(INFO) << "l2Cache hit for address: " << address;
        l1Cache.insert(address, l2Cache.read(address));
        memStack.push(address);
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
    LOG(INFO) << "Data stored in l1Cache for address: " << address;
}

void Core::handleAddInstruction() {
    MemStack& memStack = MemStack::getInstance();
    if (memStack.size() < 2) {
        LOG(ERROR) << "ADD operation requires at least two operands";
        return;
    }

    std::string operand1 = memStack.pop();
    std::string operand2 = memStack.pop();

    try {
        int result = std::stoi(operand1) + std::stoi(operand2);
        memStack.push(std::to_string(result));
    } catch (const std::invalid_argument& e) {
        LOG(ERROR) << "Invalid argument for ADD operation: " << e.what();
    } catch (const std::out_of_range& e) {
        LOG(ERROR) << "Out of range error for ADD operation: " << e.what();
    }
}

