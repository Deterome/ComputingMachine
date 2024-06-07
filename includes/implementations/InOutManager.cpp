#include "InOutManager.hpp"

InOutManager::InOutManager(InOutMethod initialIOmethod) {
	this->_currentOutputMethod = initialIOmethod;
}

void InOutManager::SetIOMethod(InOutMethod outputMethod) {
    _currentOutputMethod = outputMethod;
}

bool InOutManager::Confirm(const std::string& confirmMessage) {
	const std::string WORD_TO_CONFIRM = "Y";
	const std::string WORD_TO_DISCARD = "N";
	std::string outputConfirmMessage = confirmMessage + "(" + WORD_TO_CONFIRM + "[yes] or " + WORD_TO_DISCARD + "[no]) "; 
	if (_currentOutputMethod == InOutMethod::Console) {
		std::cout << outputConfirmMessage;
	}
	std::string inputedString;
	bool confirmed;
	while (true) {
		inputedString = this->GetString();
		if (inputedString == WORD_TO_CONFIRM) {
			confirmed = true;
			break;
		} else if (inputedString == WORD_TO_DISCARD) {
			confirmed = false;
			break;
		}
	}
	return confirmed;
}

void InOutManager::OutputString(const std::string&  message, bool addEndOfLine) {
	if (_currentOutputMethod == InOutMethod::Console) {
		std::cout << message;

		if (addEndOfLine) {
			std::cout << std::endl;
		}
	}
}

std::string InOutManager::GetString() {
	std::string enteredString;
	if (_currentOutputMethod == InOutMethod::Console) {
		std::getline(std::cin, enteredString);
	}

	return enteredString;
}

void InOutManager::ClearOutput() {
	if (_currentOutputMethod == InOutMethod::Console) {
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}
}