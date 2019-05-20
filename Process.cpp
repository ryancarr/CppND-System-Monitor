#include "Process.h"

string Process::getCmd()const
{

}

int Process::getCpu()const
{

}

int Process::getMem()const
{

}

string Process::getPid()const 
{
    return this->pid;
}

string Process::getProcess()
{
    if(!ProcessParser::isPidExisting(this->pid))
        return "";
        
    this->mem = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   " + this->user + "   " + this->mem+ "   " + this->cpu + "   " + this->upTime);
}

string Process::getUpTime()const
{

}

string Process::getUser()const
{

}

void Process::setPid(int pid)
{
    this->pid = pid;
}