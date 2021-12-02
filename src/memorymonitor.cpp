#include "../include/memorymonitor.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
std::map<std::string,uint64_t> MemMonitor::getMemStats() {
    std::fstream file("/proc/meminfo");
    std::string line;
    std::map<std::string,uint64_t> memstat;
    std::stringstream ss;
    uint64_t val{};
    while(getline(file,line)) {
        auto col_pos = line.find(':');
        std::string prop = line.substr(0,col_pos);
        //std::cout << prop << std::endl;
        line = line.substr(col_pos+1);
        line.erase(std::remove_if(line.begin(),line.end(),[](char c){return c == ' ';}),line.end());
        //std::cout << "'" << line.substr(0,line.length()-2) << "'" << std::endl;
        ss << line.substr(0,line.length()-2);
        ss >> val;
        memstat.emplace(std::make_pair(prop,val));
        ss.clear();
    }
    file.close();
    return memstat;
}

float MemMonitor::getFreeMem(std::map<std::string,uint64_t>& memstat) {
    float free_mem = memstat["MemFree"];
    float free_percentage = ( free_mem / (float)memstat["MemTotal"] ) * 100;
    return free_percentage;
}

float MemMonitor::getUsedMem(std::map<std::string,uint64_t>& memstat) {
    return 100.00 - this->getFreeMem(memstat);
}

float MemMonitor::getFreeSwapMem(std::map<std::string,uint64_t>& memstat) {
    float free_mem = memstat["SwapFree"];
    float free_percentage = ( free_mem / (float)memstat["SwapTotal"] ) * 100;
    return free_percentage;
}

float MemMonitor::getUsedSwapMem(std::map<std::string,uint64_t>& memstat) {
    return 100.00 - this->getFreeSwapMem(memstat);
}