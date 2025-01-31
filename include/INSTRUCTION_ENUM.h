#ifndef INSTRUCTION_ENUM_H
#define INSTRUCTION_ENUM_H

#include <string>
#include <unordered_map>

enum InstructionEnum {
    LOAD,
    STORE,
    INVALID
};

static InstructionEnum stringToInstruction(const std::string& str) {
    static const std::unordered_map<std::string, InstructionEnum> stringToEnumMap = {
        {"LOAD",  LOAD},
        {"STORE", STORE}
    };

    auto it = stringToEnumMap.find(str);
    return (it != stringToEnumMap.end()) ? it->second : INVALID;
}

#endif // INSTRUCTION_ENUM_H