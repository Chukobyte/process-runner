## Process Runner

A library for running a process on windows and linux.  May add MacOSX support in the future.

## Instructions

Include the `process_runner` folder within your project's include folder.  Import `#include "process_runner/process_runner.h"` in order to use `ProcessRunner`.

## Functions

```c++
bool StartProccess(const std::string &processPath, const std::string &startArgs = "")
```

Starts a process based on the `processPath`.  Can pass optional arguments to start the process.  Returns `true` if process was started successfully and `false` otherwise.

```c++
void StopProcess()
```

Stops running process.

```c++
bool IsProcessRunning() const
```

Simply checks if the process is running.

## Example

```c++
ProcessRunner processRunner;
processRunner.StartProccess("C:\\projects\\game.exe", "-log-level DEBUG");
std::cout << "Process has started!" << std::endl;

while (processRunner.IsProcessRunning()) {
    if (HasPressedESCKey()) { // Function to check if ESC is pressed
        processRunner.StopProcess();
    }
}

std::cout << "Process has stopped!" << std::endl;
```

There is also an example in [main.cpp](https://github.com/Chukobyte/process-runner/tree/main/src/main.cpp).
