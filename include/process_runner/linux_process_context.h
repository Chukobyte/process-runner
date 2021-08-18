#ifndef LINUX_PROCESS_CONTEXT_H
#define LINUX_PROCESS_CONTEXT_H

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>
#include <string>

class ProcessContext {
  private:
    pid_t pid;

    static char *ConvertStringToChar(const std::string & s) {
        char *pc = new char[s.size()+1];
        std::strcpy(pc, s.c_str());
        return pc;
    }

  public:
    void Start(const std::string &processPath, const std::string &startArgs) {
        if (IsRunning()) {
            return;
        }
        pid = fork();
        if (pid < 0) {
            std::cerr << "Error creating fork!" << std::endl;
        } else if(pid > 0) {
//            std::cout << "In parent process!" << std::endl;
        } else {
            const std::string fullStartArgs = startArgs.empty() ? processPath : processPath + " " + startArgs;
            char *args[] = ConvertStringToChar(fullStartArgs);
            execv(processPath.c_str(), args);
//            char *args[] = {processPath.c_str(), "-lh", "/home", nullptr};
//            execl(processPath.c_str(), processPath.c_str(), nullptr);
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
