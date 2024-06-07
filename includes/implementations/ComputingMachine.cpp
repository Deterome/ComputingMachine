#include "ComputingMachine.hpp"
#include "OperationsOnString.hpp"

ComputingMachine::ComputingMachine() {
    this->alphabet.push_back(EMPTY_TOKEN);
}

void ComputingMachine::ExecuteStep() {
    token currentToken;
    if (headPos < 0 || headPos >= tape.size()) {
        currentToken = EMPTY_TOKEN;
    } else {
        currentToken = this->tape[this->headPos];
    }

    ActionDescription currentAction = commandsTable[currentState][currentToken];
    if ((currentToken == currentAction.newToken || currentAction.newToken == UNINITIALIZED_TOKEN) && (this->currentState == currentAction.nextState || currentAction.nextState.size() == 0) && this->currentMoveDir == MovementDirection::STAY || isMachineStoped ) {
        isMachineStoped = true;
        return;
    }

    if (headPos < 0) {
        this->tape = currentAction.newToken + std::string(-(headPos+1), EMPTY_TOKEN) + this->tape;
        headPos = 0;
    } else if (headPos >= tape.size()) {
        this->tape += std::string(headPos - tape.size(), EMPTY_TOKEN) + currentAction.newToken;
        headPos = tape.size() -1;
    } else {
        this->tape[this->headPos] = currentAction.newToken;
    }

    this->currentState = currentAction.nextState;
    this->currentMoveDir =currentAction.moveDir;
    MoveHead();
    ClearEmptyTokens();
}

void ComputingMachine::ClearEmptyTokens() {
    while (tape[tape.size()-1] == EMPTY_TOKEN) {
        tape.erase(tape.size()-1);
    }
    while (tape[0] == EMPTY_TOKEN) {
        tape.erase(0);
    }
}

void ComputingMachine::Execute() {
    while (!isMachineStoped) {
        ExecuteStep();
    }
}

void ComputingMachine::SetHeadPos(int newHeadPos) {
    this->headPos = newHeadPos;
}

bool ComputingMachine::IsMachineStoped() const {
    return this->isMachineStoped;
}

void ComputingMachine::MoveHead() {
    switch (currentMoveDir)
    {
    case MovementDirection::LEFT:
        this->headPos--;
        break;
    case MovementDirection::RIGHT:
        this->headPos++;
        break;
    }
}

void ComputingMachine::SetCurrentState(state currentState) {
    if (std::find(states.begin(), states.end(), currentState) != states.end()) {
        this->currentState = currentState;
    } else {
        throw "Cumputing machine doesn't have such state!";
    }
}

void ComputingMachine::AddTokenToAlphabet(token newToken) {
    if (std::find(alphabet.begin(), alphabet.end(), newToken) == alphabet.end()) {
        this->alphabet.push_back(newToken);
    }
}

void ComputingMachine::AddCommand(state currentState, token commandToken, ActionDescription actDescription) {
    this->commandsTable[currentState][commandToken] = actDescription;
}

void ComputingMachine::AddState(state newState) {
    if (std::find(states.begin(), states.end(), newState) == states.end()) {
        this->states.push_back(newState);
    }
}

void ComputingMachine::SetTapeWord(word newTapeWord) {
    std::string regexStr = "([";
    regexStr += MakeStrFromArray(alphabet.data(), alphabet.size(), "");
    regexStr += "]+)";
    std::smatch regexResult;
    std::regex regex(regexStr.c_str());
    std::string processedNewTapeWord;
    while (std::regex_search(newTapeWord, regexResult, regex)) {
        processedNewTapeWord += regexResult[0];
        newTapeWord = regexResult.suffix();
    }

    this->tape = processedNewTapeWord;
}

word ComputingMachine::GetTapeWord() const {
    return this->tape;
}

std::vector<token> ComputingMachine::GetAlphabet() const {
    return this->alphabet;
}

std::vector<state> ComputingMachine::GetStates() const {
    return this->states;
}

state ComputingMachine::GetCurrentState() const {
    return this->currentState;
}

MovementDirection ComputingMachine::GetCurrentMoveDirection() const {
    return this->currentMoveDir;
}

int ComputingMachine::GetCurrentHeadPos() const {
    return this->headPos;
}