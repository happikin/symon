#include <iostream>
#include "include/cpumonitor.h"
#include "include/memorymonitor.h"
#include "include/constants.h"
#include "include/logger.h"
#include "include/util.h"

using namespace std;
using namespace std::chrono_literals;

int main()
{

    auto logs = Logger::logToConsole();
    auto p_dirs = Util::getDirs();
    Logger::logToFile(logs,Logfile::csv);

    return 0;
}