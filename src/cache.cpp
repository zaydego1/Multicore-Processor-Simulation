#include "cache.h"
#include <iostream>

/**
 * Constructor to initialize the cache with the given size, line size, and associativity.
 * It calculates the number of sets and initializes the cache lines.
 *
 * @param size - Total size of the cache in bytes.
 * @param lineSize - Size of each cache line in bytes.
 * @param associativity - Number of lines per set (e.g., 2 for 2-way associative).
 */
Cache::Cache(int size, int lineSize, int associativity)
    : size(size), lineSize(lineSize), associativity(associativity) {
    int numSets = (size / (lineSize * associativity));
    cacheLines.resize(numSets, std::vector<CacheLine>(associativity, {0, false, ""}));
}

/**
 * Checks if the given address is present in the cache (cache hit or miss).
 *
 * @param address - The memory address to look up.
 * @return true if the address is found in the cache (hit), false otherwise (miss).
 */
bool Cache::lookup(int address) {
    int index = getIndex(address);
    int tag = getTag(address);

    for (auto& line : cacheLines[index]) {
        if (line.valid && line.tag == tag) {
            std::cout << "Cache hit at address: " << address << "\n";
            return true;
        }
    }

    std::cout << "Cache miss at address: " << address << "\n";
    return false;
}

/**
 * Updates the cache with a new address and its associated data.
 * If the address is not found in the cache, it replaces a cache line.
 *
 * @param address - The memory address to update.
 * @param data - The data to store in the cache line.
 */
void Cache::update(int address, const std::string& data) {
    int index = getIndex(address);
    int tag = getTag(address);

    // Replace a line in the set with the new data
    replaceLine(index, tag, data);
}

/**
 * Replaces a cache line within the given set index.
 * Uses a simple replacement policy (e.g., replaces the first available line or the first line in the set).
 *
 * @param index - The set index where the replacement should occur.
 * @param tag - The tag associated with the new data.
 * @param data - The data to store in the cache line.
 */
void Cache::replaceLine(int index, int tag, const std::string& data) {
    for (auto& line : cacheLines[index]) {
        if (!line.valid) {
            line.tag = tag;
            line.valid = true;
            line.data = data;
            return;
        }
    }

    // If all lines are valid, replace the first line (simple replacement policy)
    cacheLines[index][0] = {tag, true, data};
}

/**
 * Displays the current state of the cache, including each set and its cache lines.
 */
void Cache::displayCacheState() const {
    for (size_t i = 0; i < cacheLines.size(); ++i) {
        std::cout << "Set " << i << ": ";
        for (const auto& line : cacheLines[i]) {
            if (line.valid) {
                std::cout << "[Tag: " << line.tag << ", Data: " << line.data << "] ";
            } else {
                std::cout << "[Invalid] ";
            }
        }
        std::cout << "\n";
    }
}

/**
 * Extracts the tag from a given memory address.
 *
 * @param address - The memory address to extract the tag from.
 * @return The tag part of the address.
 */
int Cache::getTag(int address) const {
    return address / (lineSize * cacheLines.size());
}

/**
 * Extracts the set index from a given memory address.
 *
 * @param address - The memory address to extract the index from.
 * @return The set index part of the address.
 */
int Cache::getIndex(int address) const {
    return (address / lineSize) % cacheLines.size();
}

/**
 * Extracts the offset within a cache line from a given memory address.
 *
 * @param address - The memory address to extract the offset from.
 * @return The offset part of the address.
 */
int Cache::getOffset(int address) const {
    return address % lineSize;
}




