#ifndef LINUX_PROCESS_CONTEXT_H
#define LINUX_PROCESS_CONTEXT_H

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>

class ProcessContext {
  private:
    pid_t pid;

    static std::vector<std::string> SplitString(const std::string s) {
        if (s.empty()) {
            return {};
        }
        std::vector<std::string> splitStrings;
        string temp = "";
        for(char i : s) {
            if(i==' ') {
                splitStrings.push_back(temp);
                temp = "";
            } else {
                temp.push_back(i);
            }
        }
        splitStrings.push_back(temp);
        return splitStrings;
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
            std::vector<std::string> stringArgs = SplitString(startArgs);
            int argsSize = 2 + stringArgs.size();
            char *args[argsSize] = {};
            args[0] = processPath.c_str();
            for (int i = 0; i < stringArgs.size() < i++) {
                args[i + 1] = stringArgs[i];
            }
            args[argsSize - 1] = nullptr;
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
