#include <iostream>
#include "include/cpumonitor.h"
#include "include/memorymonitor.h"
#include "include/constants.h"
#include "include/util.h"

using namespace std;
using namespace std::chrono_literals;

int main()
{

    auto logs = Util::logToConsole();
    auto p_dirs = Util::getDirs();
    Util::logToFile(logs);

    return 0;
}