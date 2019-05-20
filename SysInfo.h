#ifndef SYS_INFO_H
#define SYS_INFO_H

#include <iostream>
#include <string>
#include <vector>

#include "ProcessParser.h"
#include "Util.h"
using std::vector;

class SysInfo 
{
    private:
        vector<string> lastCpuStats;
        vector<string> currentCpuStats;
        vector<string> coresStats;
        vector<vector<string>>lastCpuCoresStats;
        vector<vector<string>>currentCpuCoresStats;
        string cpuPercent;
        float memPercent;
        string OSname;
        string kernelVer;
        long upTime;
        int totalProc;
        int runningProc;
        int threads;
        
    public:

        SysInfo()
        {
            /*
            Getting initial info about system
            Initial data for individual cores is set
            System data is set
            */
            this->getOtherCores(ProcessParser::getNumberOfCores());
            this->setLastCpuMeasures();
            this->setAttributes();
            this-> OSname = ProcessParser::getOSName();
            this-> kernelVer = ProcessParser::getSysKernelVersion();
        }
        
        vector<string> getCoresStats()const;
        string getCpuPercent()const;
        string getKernelVersion()const;
        string getMemPercent()const;
        string getOSName()const;
        void getOtherCores(int _size);
        string getRunningProc()const;
        string getThreads()const;
        string getTotalProc()const;
        long getUpTime()const;

        void setAttributes();
        void setCpuCoresStats();
        void setLastCpuMeasures();
};

#endif // SYS_INFO_H