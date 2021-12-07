#include <vector>
#include <string>
#include <dirent.h>
#include <stdlib.h>
#include <thread>
#include <ctime>
#include <fstream>
// #include <jayson.h>

// @singleton
class Logger
{
private:
    // static std::string logfile;
public:
    Logger() = delete;
    Logger(const Logger &) = delete;
    Logger(const Logger &&) = delete;
    void operator=(Logger) = delete;

    static std::string logToConsole()
    {
        std::string logfile{""};

        bool choice{true};

        std::thread th1([&]() mutable
                        {
                std::unique_ptr<CpuMonitor> cpumon = std::make_unique<CpuMonitor>();
                std::unique_ptr<MemMonitor> memmon = std::make_unique<MemMonitor>();
                logfile += "CPU Free%,MEM Free%,SWAP Free%,TimeOfLog\n";
                while (choice)
                {
                    auto cpu_data = cpumon->getCpuData();
                    logfile += std::to_string(cpu_data[idle]) + ",";
                    std::cout << "CPU Free% " << cpu_data[idle] << std::endl;
                    std::cout << "CPU Running% " << cpu_data[run] << std::endl;
                    auto memmap = memmon->getMemStats();
                    std::cout << std::endl;
                    logfile += std::to_string(memmon->getFreeMem(memmap)) + ",";
                    std::cout << "MEM Free% " << memmon->getFreeMem(memmap) << std::endl;
                    std::cout << "MEM Used% " << memmon->getUsedMem(memmap) << std::endl;
                    std::cout << std::endl;
                    logfile += std::to_string(memmon->getFreeSwapMem(memmap)) + ",";
                    std::cout << "SWAP Free% " << memmon->getFreeSwapMem(memmap) << std::endl;
                    std::cout << "SWAP Used% " << memmon->getUsedSwapMem(memmap) << std::endl;
                    std::time_t result = std::time(nullptr);
                    auto now = std::asctime(std::localtime(&result));
                    std::cout << "Time of Log " << now << std::endl;
                    logfile += std::string(now);
                    std::cout << "- - - type 'q' then press ENTER to quit - - -" << std::endl;
                } });

        std::thread th2([&]() mutable
                        {
                // type ' q ' in the console to quit the logger
                while(choice) {
                    char ch;
                    std::cin >> ch;
                    if(ch == 'q') choice = false;
                    else choice = true;
                } });

        th1.join();
        th2.join();

        return logfile;
    }

    static void logToFile(std::string& logfile, const Logfile type=Logfile::text)
    {
        // this function will make an entry of the average system stats in a log file
        switch (type)
        {
        case Logfile::text:
                [&](){
                    std::cout << "Logging to text file\n";
                    std::ofstream out("logfile.txt");
                    out << logfile;
                    out.close();
                }();
            break;
        
        case Logfile::json:
                [&](){
                    std::cout << "Logging to JSON file\n";
                }();
            break;

        case Logfile::csv:
                [&](){
                    std::cout << "Logging to CSV file\n";
                    std::ofstream out("logfile.csv");
                    out << logfile;
                    out.close();
                }();
            break;

        default:
            break;
        }
    }
};

