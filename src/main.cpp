#include <iostream>

#include "process_runner/process_runner.h"

int main(int argv, char** args) {
    char *argsTest[] = {"program", "-lh", "/home", NULL};
    std::cout << "args = " << argsTest[0] << std::endl;
    ProcessRunner processRunner;

    std::cout << "Type name of process path:" << std::endl;
    std::string processPath;
    getline(std::cin, processPath);

    std::cout << "Starting process from '" << processPath << "'!" << std::endl;
    const bool processStarted = processRunner.StartProccess(processPath);
    if (processStarted) {
        std::cout << "Process started!" << std::endl;

        while (processRunner.IsProcessRunning()) {}

        processRunner.StopProcess();
        std::cout << "Process ended!" << std::endl;
    } else {
        std::cerr << "Not able to start process at '" << processPath << "'!" << std::endl;
    }

    return 0;
}
