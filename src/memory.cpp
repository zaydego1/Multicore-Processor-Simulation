#include "memory.h"
#include <iostream>

/**
 * Reads data from the specified memory address.
 *
 * @param address - The memory address to read from.
 * @return The data stored at the given address. Returns an empty string if the address is not found.
 */
std::string Memory::read(int address) {
    if (memoryStore.find(address) != memoryStore.end()) {
        std::cout << "Memory read at address: " << address << "\n";
        return memoryStore[address];
    } else {
        std::cout << "Memory read miss at address: " << address << "\n";
        return "";
    }
}

/**
 * Writes data to the specified memory address.
 *
 * @param address - The memory address to write to.
 * @param data - The data to store at the given address.
 */
void Memory::write(int address, const std::string& data) {
    memoryStore[address] = data;
    std::cout << "Memory write at address: " << address << " with data: " << data << "\n";
}

/**
 * Displays the current state of the memory, showing all stored addresses and their data.
 */
void Memory::displayMemoryState() const {
    for (const auto& [address, data] : memoryStore) {
        std::cout << "Address: " << address << ", Data: " << data << "\n";
    }
}
