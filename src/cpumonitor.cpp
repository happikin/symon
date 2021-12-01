#include "../include/cpumonitor.h"
#include <fstream>
#include <memory>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

std::map<std::string,uint64_t> CpuMonitor::getCpuStats(std::string data) {
    const int start{};
    std::map<std::string,uint64_t> statmap;
    
    uint8_t i{};
    while(data.size() != 0) {
        std::stringstream ss;
        uint64_t i_time;

        auto end = data.find(' ');
        if(end == std::string::npos) {
            auto time = data.substr(start, end);
            ss << time;
            ss >> i_time;
            statmap.insert(make_pair(fields[i],i_time));
            break;
        };
        auto time = data.substr(start, end);
        ss << time;
        ss >> i_time;
        statmap.insert(make_pair(fields[i],i_time));
        data = data.substr(end+1);
        i++;
    }
    
    return statmap;
}

float CpuMonitor::getCpuIdletime() {
    std::string cpu;

    std::fstream file("/proc/stat");
    if(!file.is_open()) return 0;
    getline(file,cpu);
    cpu = cpu.substr(5);
    auto cpustat = this->getCpuStats(cpu);
    file.close();
    cpu.clear();

    std::this_thread::sleep_for(1000ms);
    
    std::fstream file2("/proc/stat");
    if(!file2.is_open()) return 0;
    getline(file2,cpu);
    cpu = cpu.substr(5);
    auto cpustat2 = this->getCpuStats(cpu);
    file.close();
    
    auto tot1{0};
    auto tot2{0};
    for(const auto& item:cpustat) tot1 += item.second;
    for(const auto& item:cpustat2) tot2 += item.second;

    float idle_delta = cpustat2["idle"] - cpustat["idle"];
    float total_delta = tot2 - tot1;
    auto idle_percentage = ( idle_delta / total_delta ) * 100;

    return idle_percentage;
}