#ifndef INSTRUCTION_ENUM_H
#define INSTRUCTION_ENUM_H

#include <string>
#include <unordered_map>


/**
 * @brief Enumerates the different types of instructions that can be executed by the processor.
 */
enum InstructionEnum {
    LOAD,
    STORE,
    ADD,
    INVALID
};

/**
 * @brief Converts a string to the corresponding InstructionEnum value.
 * 
 * @param str The string to convert.
 * @return The InstructionEnum value corresponding to the string.
 */
static InstructionEnum stringToInstruction(const std::string& str) {
    static const std::unordered_map<std::string, InstructionEnum> stringToEnumMap = {
        {"LOAD",  LOAD},
        {"STORE", STORE},
        {"ADD", ADD}
    };

    auto it = stringToEnumMap.find(str);
    return (it != stringToEnumMap.end()) ? it->second : INVALID;
}

#endif // INSTRUCTION_ENUM_H