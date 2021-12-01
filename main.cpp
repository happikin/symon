#include <iostream>
#include <fstream>
#include "include/cpumonitor.h"

using namespace std;

int main() {

    fstream file("/proc/stat");

    Monitor *mon = new CpuMonitor();

    const string proc = "/proc/";

    if(file.is_open()) cout << "Opened\n";
    else cout << "Not opened\n";

    string data;

    getline(file,data);

    data = data.substr(5);

    cout << "'" << data << "'" << endl; 

    auto cpustat = mon->getCpuStats(data);

    for(auto& item:cpustat) {
        cout << item.first << "->" << item.second << endl;
    }

    file.close();

    return 0;
}