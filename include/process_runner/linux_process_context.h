#ifndef LINUX_PROCESS_CONTEXT_H
#define LINUX_PROCESS_CONTEXT_H

#include <iostream>

class ProcessContext {
  private:
    bool running = false;

  public:
    ProcessContext() {
        std::cout << "Linux process context" << std::endl;
    }

    void Start(const std::string &processPath, const std::string &startArgs) {}

    void Stop() {}

    bool IsRunning() const {
        return running;
    }
};

#endif //LINUX_PROCESS_CONTEXT_H
