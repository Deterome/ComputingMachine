#include <vector>
#include <iostream>
#include "ComputingMachine.hpp"
#include "ComputingMachineViewer.hpp"
#include "ComputingMachineSetuper.hpp"
#include "InOutManager.hpp"
#ifdef _WIN32
#include <windows.h> // Заголовочный файл для Windows
#else
#include <unistd.h> // Заголовочный файл для Linux
#endif

int main() {
    InOutManager mainIOsystem(InOutMethod::Console);
    ComputingMachineSetuper computeMachSetuper;
    ComputingMachineViewer computeMachViewer;
    
    ComputingMachine computeMachine = computeMachSetuper.SetupNewComputeMachine(mainIOsystem);

    computeMachViewer.ShowMachine(computeMachine, mainIOsystem);
    while (!mainIOsystem.Confirm("Run machine?"));
    while(!computeMachine.IsMachineStoped()) {
        mainIOsystem.ClearOutput();
        
        computeMachViewer.ShowMachine(computeMachine, mainIOsystem);
        computeMachine.ExecuteStep();

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    while (!mainIOsystem.Confirm("Exit the program?"));
    return 0;
}
