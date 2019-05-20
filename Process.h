#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "ProcessParser.h"

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
private:
    string pid;
    string user;
    string cmd;
    string cpu;
    string mem;
    string upTime;

public:
    Process() {}
    Process(string pid)
    {
        this->cmd    = ProcessParser::getCmd(pid);
        this->cpu    = ProcessParser::getCpuPercent(pid);
        this->mem    = ProcessParser::getVmSize(pid);
        this->pid    = pid;
        this->upTime = ProcessParser::getProcUpTime(pid);
        this->user   = ProcessParser::getProcUser(pid);
    }

    string getCmd()const;
    int getCpu()const;
    int getMem()const;
    string getPid()const;
    string getProcess();
    string getUpTime()const;
    string getUser()const;
    
    void setPid(int pid);
};

#endif // PROCESS_H