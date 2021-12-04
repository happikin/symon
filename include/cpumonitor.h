#pragma once
#include <vector>
#include <map>
#include <sstream>
/**
 * This 
*/
class CpuMonitor {
    private:
        const std::vector<std::string> fields {
            "user",
            "nice",
            "system",
            "idle",
            "iowait",
            "irq",
            "softirq",
            "steal",
            "guest",
            "guest_nice"
        };
    public:
        CpuMonitor(/* args */) {}
        ~CpuMonitor() {}

        std::map<std::string,uint64_t> getCpuStats(std::string data);
        std::map<std::string,float> getCpuData();

};
