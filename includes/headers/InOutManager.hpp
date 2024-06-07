#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>

enum InOutMethod {
	Console
};

class InOutManager {
public:
	InOutManager(InOutMethod initialIOmethod = InOutMethod::Console);
	void SetIOMethod(InOutMethod outputMethod);
	bool Confirm(const std::string& confirmMessage);
	void OutputString(const std::string& outputMessage, bool addEndOfLine = true);
	void ClearOutput();
	std::string GetString();

private:
	InOutMethod _currentOutputMethod;
};