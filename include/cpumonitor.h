#pragma once
#include "monitor.h"
#include <vector>
#include <sstream>

class CpuMonitor : public Monitor {
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

        std::map<std::string,uint64_t> getCpuStats(std::string data) override ;
        

};
