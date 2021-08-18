#ifndef WINDOWS_PROCESS_CONTEXT_H
#define WINDOWS_PROCESS_CONTEXT_H

#include <process.h>
#include <windows.h>
#include <fstream>

class ProcessContext {
  private:
    STARTUPINFO startUpInfo;
    PROCESS_INFORMATION processInformation;
    FILE *stdOutStream = nullptr;
    std::streamoff stdOutInputStreamOffset = 0;
    std::ifstream stdOutInputStream = nullptr;

  public:
    ProcessContext() {
        // std::cout << "Windows process context" << std::endl;
    }

    void Start(const std::string &processPath, const std::string &startArgs) {
        if (IsRunning()) {
            return;
        }
        ZeroMemory(&startUpInfo, sizeof(startUpInfo));
        startUpInfo.cb = sizeof(startUpInfo);
        ZeroMemory(&processInformation, sizeof(processInformation));

        const std::string &fullStartProcessArgs = processPath + " " + startArgs;

        TCHAR startProcessArgs[fullStartProcessArgs.size()];
        strcpy(startProcessArgs, fullStartProcessArgs.c_str());

        CreateProcess(processPath.c_str(),
                      startArgs.empty() ? nullptr : startProcessArgs,
                      nullptr,
                      nullptr,
                      FALSE,
                      0,
                      nullptr,
                      nullptr,
                      &startUpInfo,
                      &processInformation
                     );
    }

    void Stop() {
        if (!IsRunning()) {
            return;
        }
        TerminateProcess(processInformation.hProcess, 0);
        CloseHandle(processInformation.hProcess);
        CloseHandle(processInformation.hThread);
        ZeroMemory(&startUpInfo, sizeof(startUpInfo));
        startUpInfo.cb = sizeof(startUpInfo);
        ZeroMemory(&processInformation, sizeof(processInformation));
    }

    bool IsRunning() const {
        if (processInformation.hProcess != nullptr && processInformation.hThread != nullptr) {
            DWORD nCode = 0;
            int result = GetExitCodeProcess(processInformation.hProcess, &nCode);
            if (result == 0) {
                // std::cerr << "Error in getting running process!\n" << nCode << std::endl;
            } else if (nCode != STILL_ACTIVE) {
                // std::cout << "Process terminated from client" << std::endl;
            } else {
                return true;
            }
        }
        return false;
    }
};

#endif //WINDOWS_PROCESS_CONTEXT_H
