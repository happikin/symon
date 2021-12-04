#include <iostream>
#include "include/cpumonitor.h"
#include "include/memorymonitor.h"
#include "include/constants.h"
#include "include/util.h"

using namespace std;
using namespace std::chrono_literals;



int main() {

    Util::logSysStats();
    auto p_dirs = Util::getDirs();
    for(auto& item:p_dirs) cout << item << endl;

    return 0;
}