#include "SysInfo.h"

#pragma region Getters
/*
 * Build a progress bar for each core
 * 
 * @return A vector of strings representing each core or an empty vector if problems occur
 */
vector<string> SysInfo::getCoresStats() const
{
    vector<string> result = vector<string>();
    for (int i = 0; i < this->coresStats.size(); i++)
    {
        string temp = ("cpu" + to_string(i) +": ");
        float check = stof(this->coresStats[i]);
        
        if (!check || this->coresStats[i] == "nan")
        {
            return vector<string>();
        }
        
        temp += "  " + Util::getProgressBar(this->coresStats[i]);
        result.push_back(temp);
    }
    return result;
}

/*
 * Returns a string representing the current CPU percent
 * 
 * @return string
 * 
 */
string SysInfo::getCpuPercent() const
{
    return this->cpuPercent;
}

/*
 * Returns a string representing the current kernel version
 * 
 * @return string
 * 
 */
string SysInfo::getKernelVersion() const
{
    return this->kernelVer;
}

/*
 * Returns the current memory percent used as a string
 * 
 * @return string
 * 
 */
string SysInfo::getMemPercent() const
{
    return to_string(this->memPercent);
}

/*
 * Returns the OS name as a string
 * 
 * @return string
 * 
 */
string SysInfo::getOSName() const
{
    return this->OSname;
}

/*
 * Resizes all CPU Core Stats members to hold the appropriate number of stats
 * 
 * @param _size An integer representing how many cores are in the system
 * 
 */
void SysInfo::getOtherCores(int _size)
{
    // When number of cores is detected, vectors are modified to fit incoming data
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

/*
 * Returns a string representing a running process
 * 
 * @return string
 * 
 */
string SysInfo::getRunningProc() const
{
    return to_string(this->runningProc);
}

/*
 * Returns a string representing current thread count
 * 
 * @return string
 * 
 */
string SysInfo::getThreads() const
{
    return to_string(this->threads);
}

/*
 * Returns a string representing total process count
 * 
 * @return string
 * 
 */
string SysInfo::getTotalProc() const
{
    return to_string(this->totalProc);
}

/*
 * Returns a long integer prepresenting the system uptime
 * 
 * @return long
 * 
 */
long SysInfo::getUpTime() const
{
    return this->upTime;
}
#pragma endregion

#pragma region Setters
/*
 * Sets the last CPU stats - total CPU usage as a percent
 */
void SysInfo::setLastCpuMeasures()
{
    this->lastCpuStats = ProcessParser::getSysCpuPercent("");
}

/*
 * Refreshes CPU core stats, existing stats are backed up into lastCpuCoreStats
 */
void SysInfo::setCpuCoresStats()
{
    // Getting data from files (previous data is required)
    for(int i=0;i<this->currentCpuCoresStats.size();i++)
        this->currentCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));

    // after acquirement of data we are calculating every core percentage of usage
    for(int i=0;i<this->currentCpuCoresStats.size();i++)
        this->coresStats[i] = ProcessParser::CalculateCpuStats(this->lastCpuCoresStats[i],this->currentCpuCoresStats[i]);

    this->lastCpuCoresStats = this->currentCpuCoresStats;
}

/*
 * Initializes or refreshes SysInfo object
 */
void SysInfo::setAttributes()
{
    // Getting parsed data
    this-> memPercent = ProcessParser::getSysRamPercent();
    this-> upTime = ProcessParser::getSysUpTime();
    this-> totalProc = ProcessParser::getTotalNumberOfProcesses();
    this-> runningProc = ProcessParser::getNumberOfRunningProcesses();
    this-> threads = ProcessParser::getTotalThreads();
    this->currentCpuStats = ProcessParser::getSysCpuPercent("");
    this->cpuPercent = ProcessParser::CalculateCpuStats(this->lastCpuStats,this->currentCpuStats);
    this->lastCpuStats = this->currentCpuStats;
    this->setCpuCoresStats();
}
#pragma endregion