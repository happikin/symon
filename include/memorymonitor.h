#pragma once
#include <map>
#include <string>
class MemMonitor {
    private:
        
    public:
        MemMonitor() {}
        ~MemMonitor() {}
        std::map<std::string,uint64_t> getMemStats();
        float getFreeMem(std::map<std::string,uint64_t>& memstat);
        float getUsedMem(std::map<std::string,uint64_t>& memstat);
        float getFreeSwapMem(std::map<std::string,uint64_t>& memstat);
        float getUsedSwapMem(std::map<std::string,uint64_t>& memstat);
};