#include "ProcessParser.h"

#pragma region Getters
/*
 *
 */
string ProcessParser::getCmd(string pid)
{ 

}

/*
 *
 */
string ProcessParser::getCpuPercent(string pid)
{
    string line;
    float result;
    ifstream inputStream;

    // Read data from /proc/$$/stat
    // Process data into a vector<string>
    
    float userTime = stof(ProcessParser::getProcUpTime(pid));

    /* man proc  search for /proc/[pid]/stat
    //int utime;                    /** user mode jiffies **/
    //int stime;                    /** kernel mode jiffies **/
    //int cutime;                   /** user mode jiffies with childs **/
    //int cstime;                   /** kernel mode jiffies with childs **/ */
    
    //float scheduledTime         = 14
    //float childUserTime         = 15
    //float childScheduledtime    = 16
    
    //int starttime; /** 20 **/     /** Time the process started after system boot **/
    //float startTime = 21 according to man proc

    float systemUpTime = ProcessParser::getSysUpTime();    
    float frequency  = sysconf(_SC_CLK_TCK);

    //float totalTime = upTime + stime + cutime + cstime;
    //float seconds = systemUpTime - (startTime/frequency);

    //result = 100.0 * ((totalTime/frequency)/seconds);

    return to_string(result);
}

/*
 *
 */
int ProcessParser::getNumberOfCores()
{
    
}

/*
 *
 */
int ProcessParser::getNumberOfRunningProcesses()
{
    
}

/*
 *
 */
string ProcessParser::getOSName()
{
    
}

/*
 *
 */
vector<string> ProcessParser::getPidList()
{
    
}

/*
 *
 */
string ProcessParser::getProcUpTime(string pid)
{
    
}

/*
 *
 */
string ProcessParser::getProcUser(string pid)
{
    
}

/*
 *
 */
vector<string> ProcessParser::getSysCpuPercent(string coreNumber = "")
{
    
}

/*
 *
 */
string ProcessParser::getSysKernelVersion()
{
    
}

/*
 *
 */
float ProcessParser::getSysRamPercent()
{
    
}

/*
 *
 */
long int ProcessParser::getSysUpTime()
{
    
}

/*
 *
 */
int ProcessParser::getTotalNumberOfProcesses()
{
    
}

/*
 *
 */
int ProcessParser::getTotalThreads()
{
    
}

/*
 * Get the memory size of a given process id
 * 
 * @param pid String representing the Process ID number
 * 
 * @return String representing the amount of memory being used in MB
 */
string ProcessParser::getVmSize(string pid)
{
    // Using code provided by the lecture
    
    // Declaring search attribute for file
    string searchTerm = "VmSize";

    string line;
    float result;
    string value;

    // Opening stream for specific file
    ifstream inputStream;
    Util::getStream((Path::basePath + pid + Path::statusPath), inputStream);
    
    // Search line by line for the searchTerm
    while(std::getline(inputStream, line))
    {
        // Check to see if the line starts with searchTerm
        if (line.compare(0, searchTerm.size(),searchTerm) == 0)
        {
            // Use sstream to slice the string and place in a vector
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);

            //conversion kB -> MB
            result = (stof(values[1])/float(1024));
            break;
        }
    }
    return to_string(result);
}
#pragma endregion

/*
 *
 */
bool ProcessParser::isPidExisting(string pid)
{
    
}

/*
 *
 */
string ProcessParser::PrintCpuStats(vector<string> values1, vector<string> values2)
{
    
}