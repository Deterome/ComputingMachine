#include "ComputingMachineViewer.hpp"
#include "OperationsOnString.hpp"

void ComputingMachineViewer::ShowMachine(const ComputingMachine& computeMach, InOutManager& ioManager) const {
    std::string outputString;
    auto machineAlphabet = computeMach.GetAlphabet();
    auto machineStates = computeMach.GetStates();
    outputString += "Machine alphabet: " + MakeStrFromArray(machineAlphabet.data(), machineAlphabet.size()) + "\n";
    outputString += "Machine states: " + MakeStrFromArray(machineStates.data(), machineStates.size()) + "\n";
    outputString += "\n";
    outputString += "Machine current state: " + computeMach.GetCurrentState() + "\n";
    outputString += "Machine current movement: ";
    switch (computeMach.GetCurrentMoveDirection())
    {
    case MovementDirection::LEFT:
        outputString += "LEFT";
        break;
    case MovementDirection::RIGHT:
        outputString += "RIGHT";
        break;
    default:
        outputString += "STAY";
        break;
    }
    outputString += "\n";
    outputString += "\n";
    outputString += "\n";
    int headOffset;
    int tapeOffset;
    int headPos = computeMach.GetCurrentHeadPos();
    if (headPos < 0) {
        tapeOffset = -headPos;
        headOffset = 0;
    } else {
        tapeOffset = 0;
        headOffset = headPos;
    }
    outputString += std::string(headOffset, ' ') + HEAD_SYMBOL + "\n";
    outputString += std::string(tapeOffset, ' ') + MakeStrFromArray(computeMach.GetTapeWord().data(), computeMach.GetTapeWord().size(), "") + "\n";
    ioManager.OutputString(outputString);
}