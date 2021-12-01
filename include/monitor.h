#pragma once
#include <map>
#include <string>

class Monitor {
    private:
        
    public:
        virtual std::map<std::string,uint64_t> getCpuStats(std::string) = 0;
        virtual ~Monitor() {};
};