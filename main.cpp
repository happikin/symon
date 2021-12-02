#include <iostream>
#include <memory>
#include "include/cpumonitor.h"
#include "include/memorymonitor.h"
#include "include/constants.h"
using namespace std;

int main() {
    std::unique_ptr<CpuMonitor> cpumon = std::make_unique<CpuMonitor>();
    auto cpu_data = cpumon->getCpuData();
    cout << "CPU Free% " << cpu_data[idle] << endl;
    cout << "CPU Running% " << cpu_data[run] << endl;
    std::unique_ptr<MemMonitor> memmon = std::make_unique<MemMonitor>();
    auto memmap = memmon->getMemStats();
    // for(const auto& item:memmap) {
    //     cout << item.first << " " << item.second << endl;
    // }
    cout << endl;
    cout << "MEM Free% " << memmon->getFreeMem(memmap) << endl;
    cout << "MEM Used% " << memmon->getUsedMem(memmap) << endl;
    cout << endl;
    cout << "SWAP Free% " << memmon->getFreeSwapMem(memmap) << endl;
    cout << "SWAP Used% " << memmon->getUsedSwapMem(memmap) << endl;
    return 0;
}