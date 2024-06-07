#pragma once
#include <string>
#include "InOutManager.hpp"
#include "ComputingMachine.hpp"

class ComputingMachineViewer {
public:
    void ShowMachine(const ComputingMachine& computeMach, InOutManager& ioManager) const;
private:
    const char HEAD_SYMBOL = '#';
};