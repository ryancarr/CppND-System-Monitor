#ifndef PROCESS_PARSER_H
#define PROCESS_PARSER_H

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <iterator>
#include <math.h>
#include <thread>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include "Constants.h"
#include "Util.h"

using std::getline;
using std::isdigit;
using std::istringstream;
using std::istream_iterator;
using std::stof;
using std::unordered_map;
using std::vector;



class ProcessParser{
    private:
        static vector<string> SplitString(string, string);
    public:
        static string getCmd(string);
        static string getCpuPercent(string);
        static int getNumberOfCores();
        static int getNumberOfRunningProcesses();
        static string getOSName();
        static vector<string> getPidList();
        static string getProcUser(string);
        static string getProcUpTime(string);
        static float getSysActiveCpuTime(vector<string>);
        static vector<string> getSysCpuPercent(string);
        static float getSysIdleCpuTime(vector<string>);
        static string getSysKernelVersion();
        static float getSysRamPercent();
        static long getSysUpTime();
        static int getTotalNumberOfProcesses();
        static int getTotalThreads();
        static string getVmSize(string);
        static string CalculateCpuStats(vector<string>, vector<string>);
        static bool isPidExisting(string);
};

#endif // PROCESS_PARSER_H