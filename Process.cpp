#include "Process.h"

/*
 * Default Process Constructor - Doesn't really do anything useful
 */
Process::Process()
{
    // Default constructor
}

/*
 * Process Constructor - Assign values to all private members
 * 
 * @param pid Generate a new process object based on a specific PID
 * 
 */
Process::Process(string pid)
{
    this->cmd    = ProcessParser::getCmd(pid);
    this->cpu    = ProcessParser::getCpuPercent(pid);
    this->mem    = ProcessParser::getVmSize(pid);
    this->pid    = pid;
    this->upTime = ProcessParser::getProcUpTime(pid);
    this->user   = ProcessParser::getProcUser(pid);
}

/*
 * Returns the command line location of the current process
 * 
 * @return string Absolute path of command
 * 
 */
string Process::getCmd() const
{
    return this->cmd;
}

/*
 * Returns the CPU usage of the current process
 * 
 * @return int representing the cpu usage
 * 
 */
int Process::getCpu() const
{
    return stoi(this->cpu);
}

/*
 * Returns the memory usage of the current process
 * 
 * @return int representing the memory usage
 * 
 */
int Process::getMem() const
{
    return stoi(this->mem);
}

/*
 * Returns the PID of the current process
 * 
 * @return string representing the PID of this process
 * 
 */
string Process::getPid() const 
{
    return this->pid;
}

/*
 * Refresh and return stats for the current process
 */
string Process::getProcess()
{
    if(!ProcessParser::isPidExisting(this->pid))
        return "";
        
    this->mem = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   " + 
            ProcessParser::getProcUser(this->pid).substr(0, 5) + "   " +
            this->cpu + "   " +
            this->mem.substr(0,5) + "M    " +
            this->upTime + "   " +
            this->cmd.substr(0,20));
}

/*
 * Returns a string representing the total uptime of the current process
 * 
 * @return string representing the total uptime
 * 
 */
string Process::getUpTime() const
{
    // Might need to run this through Util::convertToTime()
    return this->upTime;
}

/*
 * Returns a string representing the owner of the current process
 * 
 * @return string representing a user name
 * 
 */
string Process::getUser() const
{
    return this->user;
}

/*
 * Sets the pid of the current process
 * 
 * @param int representing the PID to be assigned to this process
 * 
 */
void Process::setPid(int pid)
{
    this->pid = pid;
}