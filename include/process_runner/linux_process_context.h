#ifndef LINUX_PROCESS_CONTEXT_H
#define LINUX_PROCESS_CONTEXT_H

#include <iostream>
#include <unistd.h>
#include <csignal.h>
#include <sys/types.h>
#include <cstdlib.h>
#include <sys/wait.h>

class ProcessContext {
  private:
    pid_t pid;

  public:
    void Start(const std::string &processPath, const std::string &startArgs) {
        if (IsRunning()) {
            return;
        }
        pid = fork();
        switch(pid) {
        case -1:
            std::cout << "Error creating fork!" << std::endl;
            break;
        case 0:
            execl(processPath.c_str(), 0, 0);
            break;
        default:
            break;
        }
    }

    void Stop() {
        if (!IsRunning()) {
            return;
        }
        int status;
        kill(pid, &status);
    }

    bool IsRunning() const {
        int status;

        waitpid(pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            std::cout << "Process terminated!" << std::endl;
            return false;
        }
        return true;
    }
};

#endif //LINUX_PROCESS_CONTEXT_H
