#pragma once
#include <string>

template<typename T>
std::string MakeStrFromArray(const T* arrayPtr, int arrayLength, std::string separator = ",") {
    std::string outputStr;
     for (int elId = 0; elId < arrayLength; elId++) {
        if (elId != 0) outputStr += separator;
        outputStr += arrayPtr[elId];
    }
    return outputStr;
}
