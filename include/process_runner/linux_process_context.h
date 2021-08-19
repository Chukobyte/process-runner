#ifndef LINUX_PROCESS_CONTEXT_H
#define LINUX_PROCESS_CONTEXT_H

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>
#include <algorithm>

class ProcessContext {
  private:
    pid_t pid;

    static std::vector<std::string> SplitString(const std::string s) {
        if (s.empty()) {
            return {};
        }
        std::vector<std::string> splitStrings;
        std::string temp = "";
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

    std::vector<char*> GetFullArgs(const std::string &processPath, const std::string &startArgs) {
        std::vector<char*> args;
        const std::string fullStartArgs = startArgs.empty() ? processPath : processPath + " " + startArgs;
        std::vector<std::string> splitStringArgs = SplitString(fullStartArgs);
        std::transform(splitStringArgs.begin(), splitStringArgs.end(), std::back_inserter(args),
        [](std::string &s) {
            s.push_back(0);
            return &s[0];
        });
        args.push_back(nullptr);
        return args;
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
            std::vector<char*> args = GetFullArgs(processPath, startArgs);
            execv(processPath.c_str(), args.data());
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
