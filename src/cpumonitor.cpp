#include "../include/cpumonitor.h"

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