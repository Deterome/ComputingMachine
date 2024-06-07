#pragma once
#include "ComputingMachine.hpp"
#include "InOutManager.hpp"
#include <array>
#include <math.h>
#include <algorithm>

class ComputingMachineSetuper {
public:
    ComputingMachine SetupNewComputeMachine(InOutManager& setuperIOsystem);
private:
    void SetupAlphabet(ComputingMachine& compMach, InOutManager& setuperIOsystem);
    void SetupStates(ComputingMachine& compMach, InOutManager& setuperIOsystem);
    void SetupCommands(ComputingMachine& compMach, InOutManager& setuperIOsystem);
    void InitTape(ComputingMachine& compMach, InOutManager& setuperIOsystem);
    void SetupInitialState(ComputingMachine& compMach, InOutManager& setuperIOsystem);

    std::array<token, 2> defaultAlphabet = {'0', '1'};
};