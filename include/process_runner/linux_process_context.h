#ifndef LINUX_PROCESS_CONTEXT_H
#define LINUX_PROCESS_CONTEXT_H

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
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
        if (pid < 0) {
            std::cout << "Error creating fork!" << std::endl;
        } else if(pid > 0) {
            std::cout << "In parent process!" << std::endl;
        } else {
            std::cout << "Executing child process!" << std::endl;
            int result = execl(processPath.c_str(), processPath.c_str(), nullptr);
            std::cout << "Start result = " << result << std::endl;
        }
    }

    void Stop() {
        if (!IsRunning()) {
            return;
        }
        kill(pid, SIGUSR1);
    }

    bool IsRunning() const {
        while(waitpid(-1, 0, WNOHANG) > 0) {
            // Wait for defunct....
        }
        if (kill(pid, 0) == 0) {
            return true;
        }
        return false;
    }
};

#endif //LINUX_PROCESS_CONTEXT_H
