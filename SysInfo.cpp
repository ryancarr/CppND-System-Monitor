#include "SysInfo.h"

#pragma region Getters
vector<string> SysInfo::getCoresStats() const
{

}

string SysInfo::getCpuPercent() const
{
    return this->cpuPercent;
}

string SysInfo::getKernelVersion() const
{
    return this->kernelVer;
}

string SysInfo::getMemPercent() const
{
    return to_string(this->memPercent);
}

string SysInfo::getOSName() const
{
    return this->OSname;
}

void SysInfo::getOtherCores(int _size)
{
    //when number of cores is detected, vectors are modified to fit incoming data
    this->coresStats = vector<string>();
    this->coresStats.resize(_size);
    this->lastCpuCoresStats = vector<vector<string>>();
    this->lastCpuCoresStats.resize(_size);
    this->currentCpuCoresStats = vector<vector<string>>();
    this->currentCpuCoresStats.resize(_size);
    
    for(int i=0;i<_size;i++)
    {
        this->lastCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));
    }
}

string SysInfo::getRunningProc() const
{
    return to_string(this->runningProc);
}

string SysInfo::getThreads() const
{
    return to_string(this->threads);
}

string SysInfo::getTotalProc() const
{
    return to_string(this->totalProc);
}

long SysInfo::getUpTime() const
{
    return this->upTime;
}
#pragma endregion

#pragma region Setters
void SysInfo::setLastCpuMeasures()
{
 this->lastCpuStats = ProcessParser::getSysCpuPercent();
}

void SysInfo::setCpuCoresStats()
{
    // Getting data from files (previous data is required)
    for(int i=0;i<this->currentCpuCoresStats.size();i++)
    {
        this->currentCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));
    }

    for(int i=0;i<this->currentCpuCoresStats.size();i++)
    {
        // after acquirement of data we are calculating every core percentage of usage
        this->coresStats[i] = ProcessParser::PrintCpuStats(this->lastCpuCoresStats[i],this->currentCpuCoresStats[i]);
    }

    this->lastCpuCoresStats = this->currentCpuCoresStats;
}

void SysInfo::setAttributes()
{
    // getting parsed data
    this-> memPercent = ProcessParser::getSysRamPercent();
    this-> upTime = ProcessParser::getSysUpTime();
    this-> totalProc = ProcessParser::getTotalNumberOfProcesses();
    this-> runningProc = ProcessParser::getNumberOfRunningProcesses();
    this-> threads = ProcessParser::getTotalThreads();
    this->currentCpuStats = ProcessParser::getSysCpuPercent();
    this->cpuPercent = ProcessParser::PrintCpuStats(this->lastCpuStats,this->currentCpuStats);
    this->lastCpuStats = this->currentCpuStats;
    this->setCpuCoresStats();
}
#pragma endregion