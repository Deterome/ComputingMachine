#pragma once
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <regex>

using token = char;
using word = std::string;
using state = std::string;

const token EMPTY_TOKEN = '_';
const token UNINITIALIZED_TOKEN = ' ';

enum MovementDirection {
    LEFT,
    RIGHT,
    STAY
};

struct ActionDescription {
    token newToken = UNINITIALIZED_TOKEN;
    MovementDirection moveDir = MovementDirection::STAY;
    state nextState;
};

class ComputingMachine {
public:
    ComputingMachine();
    void Execute();
    void ExecuteStep();

    void AddTokenToAlphabet(token newToken);
    std::vector<token> GetAlphabet() const;

    void AddState(state newState);
    void SetCurrentState(state currentState);
    std::vector<state> GetStates() const;
    state GetCurrentState() const;

    void AddCommand(state currentState, token commandToken, ActionDescription actDescription);

    void SetHeadPos(int newHeadPos);

    void SetTapeWord(word newTapeWord);
    word GetTapeWord() const;

    bool IsMachineStoped() const;

    MovementDirection GetCurrentMoveDirection() const;
    int GetCurrentHeadPos() const;
private:
    void MoveHead();
    void ClearEmptyTokens();
    bool isMachineStoped = false;
    std::vector<token> alphabet;
    std::vector<state> states;
    MovementDirection currentMoveDir = MovementDirection::RIGHT;
    std::map<state, std::map<token, ActionDescription>> commandsTable;

    int headPos = 0;
    state currentState;
    word tape;
};