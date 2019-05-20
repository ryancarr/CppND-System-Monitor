#ifndef PROCESS_PARSER_H
#define PROCESS_PARSER_H

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <thread>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "constants.h"

using std::ifstream;
using std::string;
using std::vector;



class ProcessParser{
    private:
        ifstream stream;
    public:
        static string getCmd(string);
        static string getCpuPercent(string);
        static int getNumberOfCores();
        static int getNumberOfRunningProcesses();
        static string getOSName();
        static vector<string> getPidList();
        static string getProcUser(string);
        static string getProcUpTime(string);
        static vector<string> getSysCpuPercent(string);
        static string getSysKernelVersion();
        static float getSysRamPercent();
        static long int getSysUpTime();
        static int getTotalNumberOfProcesses();
        static int getTotalThreads();
        static string getVmSize(string);
        static bool isPidExisting(string);
        static string PrintCpuStats(vector<string>, vector<string>);
};

#endif // PROCESS_PARSER_H