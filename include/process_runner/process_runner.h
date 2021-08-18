#ifndef PROCESS_RUNNER_H
#define PROCESS_RUNNER_H

#include <string>
#include <sys/stat.h>

#ifdef __linux__
#include "linux_process_context.h"
#elif _WIN32
#include "windows_process_context.h"
#else
// os not supported!
#endif

class ProcessRunner {
  private:
    ProcessContext processContext;

    static bool DoesFileExist(const std::string &fileName) {
        struct stat buffer {};
        return(stat(fileName.c_str(), &buffer) == 0);
    }
  public:
    bool StartProccess(const std::string &processPath, const std::string &startArgs = "") {
        if (DoesFileExist(processPath)) {
            processContext.Start(processPath, startArgs);
            return true;
        }
        return false;
    }

    void StopProcess() {
        processContext.Stop();
    }

    bool IsProcessRunning() const {
        return processContext.IsRunning();
    }
};

#endif //PROCESS_RUNNER_H
