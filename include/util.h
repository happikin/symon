#include <vector>
#include <string>
#include <dirent.h>
#include <stdlib.h>
#include <thread>

// @singleton
class Util {
    private:
        
    public:

        Util() = delete;
        Util(const Util&) = delete;
        Util(const Util&&) = delete;
        void operator=(Util) = delete;

        static bool is_numeric(std::string dirname) {
            for(char& ch:dirname) {
                if(ch > 57 || ch < 48) return false;
            } return true;
        }
        static std::vector<std::string> getDirs() {
            DIR *dir;
            dirent *ent;
            std::vector<std::string> dirs;
            if ((dir = opendir ("/proc/")) != NULL) {
                while ((ent = readdir (dir)) != NULL) {
                    if(ent->d_type == DT_DIR) {
                        if(is_numeric(std::string(ent->d_name)))
                            dirs.push_back(std::string(ent->d_name));
                    }
                }
                closedir (dir);
            } else {
                /* could not open directory */
                perror ("");
            }
            return dirs;
        }

        static void logSysStats() {
            
            bool choice{true};

            std::thread th1([&]() mutable {
                std::unique_ptr<CpuMonitor> cpumon = std::make_unique<CpuMonitor>();
                std::unique_ptr<MemMonitor> memmon = std::make_unique<MemMonitor>();

                while (choice)
                {
                    auto cpu_data = cpumon->getCpuData();
                    std::cout << "CPU Free% " << cpu_data[idle] << std::endl;
                    std::cout << "CPU Running% " << cpu_data[run] << std::endl;
                    auto memmap = memmon->getMemStats();
                    std::cout << std::endl;
                    std::cout << "MEM Free% " << memmon->getFreeMem(memmap) << std::endl;
                    std::cout << "MEM Used% " << memmon->getUsedMem(memmap) << std::endl;
                    std::cout << std::endl;
                    std::cout << "SWAP Free% " << memmon->getFreeSwapMem(memmap) << std::endl;
                    std::cout << "SWAP Used% " << memmon->getUsedSwapMem(memmap) << std::endl;
                    std::cout << "- - - - - - - - - - - - -" << std::endl;
                }
            });

            std::thread th2([&]() mutable {
                // type ' q ' in the console to quit the logger
                while(choice) {
                    char ch;
                    std::cin >> ch;
                    if(ch == 'q') choice = false;
                    else choice = true;
                }
            });
            
            th1.join();
            th2.join();
            
        }
};