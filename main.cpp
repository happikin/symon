#include <iostream>
#include <memory>
#include "include/cpumonitor.h"

using namespace std;

int main() {
    std::unique_ptr<CpuMonitor> mon = std::make_unique<CpuMonitor>();

    cout << "CPU Free% " << mon->getCpuIdletime() << endl;
    
    return 0;
}