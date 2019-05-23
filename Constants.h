#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
using std::string;

enum CPUStates{
	S_USER = 1,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

class Path
{
    public:
        static const string basePath;
        static const string cmdPath;
        static const string statusPath;
        static const string statPath;
        static const string upTimePath;
        static const string memInfoPath;
        static const string versionPath;
};

#endif // CONSTANTS_H