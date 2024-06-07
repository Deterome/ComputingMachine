#include "ComputingMachineSetuper.hpp"
#include "OperationsOnString.hpp"

ComputingMachine ComputingMachineSetuper::SetupNewComputeMachine(InOutManager& setuperIOsystem) {
    ComputingMachine newComputeMachine;

    SetupAlphabet(newComputeMachine, setuperIOsystem);
    
    setuperIOsystem.ClearOutput();

    SetupStates(newComputeMachine, setuperIOsystem);

    setuperIOsystem.ClearOutput();

    SetupCommands(newComputeMachine, setuperIOsystem);

    setuperIOsystem.ClearOutput();

    InitTape(newComputeMachine, setuperIOsystem);

    setuperIOsystem.ClearOutput();

    SetupInitialState(newComputeMachine, setuperIOsystem);

    setuperIOsystem.ClearOutput();

    return newComputeMachine;
}

void ComputingMachineSetuper::SetupInitialState(ComputingMachine& compMach, InOutManager& setuperIOsystem) {
    setuperIOsystem.OutputString("Setting up initial state");

    setuperIOsystem.OutputString("Enter initial state: ", false);
    auto machStates = compMach.GetStates();
    state initialState;
    while (std::find(machStates.begin(), machStates.end(), (initialState = setuperIOsystem.GetString())) == machStates.end()) {
        setuperIOsystem.OutputString("Machine doesn't have state " + initialState);
        setuperIOsystem.OutputString("Pick one of next states: " + MakeStrFromArray(machStates.data(), machStates.size()));
    }

    compMach.SetCurrentState(initialState);
}

void ComputingMachineSetuper::SetupStates(ComputingMachine& compMach, InOutManager& setuperIOsystem) {
    setuperIOsystem.OutputString("Setting up states");
    
    setuperIOsystem.OutputString("Enter states of compute machine:");
    std::string newState;
    while((newState = setuperIOsystem.GetString()).length() != 0) {
        compMach.AddState(newState);
    }
}

void ComputingMachineSetuper::SetupCommands(ComputingMachine& compMach, InOutManager& setuperIOsystem) {
    setuperIOsystem.OutputString("Setting up commands");

    auto machAlphabet = compMach.GetAlphabet();
    auto machStates = compMach.GetStates();

    const std::string LEFT_MOVEMENT_STR = "L";
    const std::string RIGHT_MOVEMENT_STR = "R";
    const std::string STAY_MOVEMENT_STR = "S";
    setuperIOsystem.OutputString("Setting rules");
    setuperIOsystem.OutputString("Action format: {new token (from machine alphabet), movement direction (" + LEFT_MOVEMENT_STR +" [left], " + RIGHT_MOVEMENT_STR +" [right], " + STAY_MOVEMENT_STR +" [stay]), next state (from machine states list)}");
    setuperIOsystem.OutputString("Machine states: " + MakeStrFromArray(machStates.data(), machStates.size()));
    state stateToSetup;
    while (true) {
        setuperIOsystem.OutputString("Enter state to setup actions:");
        
        stateToSetup = setuperIOsystem.GetString();
        while (std::find(machStates.begin(), machStates.end(), stateToSetup) == machStates.end() && stateToSetup.size() != 0) {
            setuperIOsystem.OutputString("Invalid state!");
            setuperIOsystem.OutputString("Pick one of next states: " + MakeStrFromArray(machStates.data(), machStates.size()));
            stateToSetup = setuperIOsystem.GetString();
        }
        if (stateToSetup.size() == 0) {
            break;
        }

        if (std::find(machStates.begin(), machStates.end(), stateToSetup) != machStates.end()) {
            for (const auto& currentToken: machAlphabet) {
                setuperIOsystem.OutputString("Enter action of " + stateToSetup + " state at token " + currentToken);

                setuperIOsystem.OutputString("New token: ", false);
                token newToken;
                while (std::find(machAlphabet.begin(), machAlphabet.end(), (newToken = setuperIOsystem.GetString()[0])) == machAlphabet.end()) {
                    setuperIOsystem.OutputString("Invalid token!");
                    setuperIOsystem.OutputString("Pick one of next tokens: " + MakeStrFromArray(machAlphabet.data(), machAlphabet.size()));
                }

                setuperIOsystem.OutputString("Movement direction: ", false);
                std::string moveDirStr = setuperIOsystem.GetString();
                MovementDirection moveDir;
                if (moveDirStr == LEFT_MOVEMENT_STR) {
                    moveDir = MovementDirection::LEFT;
                } else if (moveDirStr == RIGHT_MOVEMENT_STR) {
                    moveDir = MovementDirection::RIGHT;
                } else if (moveDirStr == STAY_MOVEMENT_STR) {
                    moveDir = MovementDirection::STAY;
                } else {
                    setuperIOsystem.OutputString("Invalid movement entered! STAY movement setted");
                    moveDir = MovementDirection::STAY;
                }

                setuperIOsystem.OutputString("Next state: ", false);
                state nextState;
                while (std::find(machStates.begin(), machStates.end(), (nextState = setuperIOsystem.GetString())) == machStates.end()) {
                    setuperIOsystem.OutputString("Invalid state!");
                    setuperIOsystem.OutputString("Pick one of next states: " + MakeStrFromArray(machStates.data(), machStates.size()));
                }

                compMach.AddCommand(stateToSetup, currentToken, {newToken, moveDir, nextState});
            }
        } else {
            setuperIOsystem.OutputString("Machine doesn\'t have state \"" + stateToSetup+"\"");
        }
        setuperIOsystem.OutputString(std::string(20, '_'));
    }
}

void ComputingMachineSetuper::InitTape(ComputingMachine& compMach, InOutManager& setuperIOsystem) {
    setuperIOsystem.OutputString("Initializing the tape");

    setuperIOsystem.OutputString("Enter initial word of computing machine:");
    std::string tapeWord = setuperIOsystem.GetString();
    compMach.SetTapeWord(tapeWord);
}

void ComputingMachineSetuper::SetupAlphabet(ComputingMachine& compMach, InOutManager& setuperIOsystem) {
    setuperIOsystem.OutputString("Setting up the alphabet");

    std::string setupAlphabetStr = "Setup alphabet? (default: [";
    setupAlphabetStr += MakeStrFromArray(defaultAlphabet.data(), defaultAlphabet.size());
    setupAlphabetStr += "]): ";

    if (setuperIOsystem.Confirm(setupAlphabetStr)) {
        setuperIOsystem.OutputString("Enter alphabet of compute machine:");
        std::string newTokenStr;
        while((newTokenStr = setuperIOsystem.GetString()).length() != 0) {
            compMach.AddTokenToAlphabet(newTokenStr[0]);
        }
    } else {
        for (auto& token: defaultAlphabet) {
            compMach.AddTokenToAlphabet(token);
        }
    }
}