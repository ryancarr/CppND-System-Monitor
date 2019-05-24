#ifndef SYS_INFO_H
#define SYS_INFO_H

#include <iostream>
#include <string>
#include <vector>

#include "ProcessParser.h"
using std::vector;

class SysInfo 
{
    private:
        vector<string> coresStats;
        string cpuPercent;        
        vector<vector<string>> lastCpuCoresStats;
        vector<string> currentCpuStats;
        string kernelVer;
        vector<vector<string>> currentCpuCoresStats;
        vector<string> lastCpuStats;
        float memPercent;
        string OSname;
        int runningProc;
        int threads;
        int totalProc;
        long upTime;
        
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
        
        vector<string> getCoresStats() const;
        string getCpuPercent() const;
        string getKernelVersion() const;
        string getMemPercent() const;
        string getOSName() const;
        void getOtherCores(int _size);
        string getRunningProc() const;
        string getThreads() const;
        string getTotalProc() const;
        long getUpTime() const;

        void setAttributes();
        void setCpuCoresStats();
        void setLastCpuMeasures();
};

#endif // SYS_INFO_H