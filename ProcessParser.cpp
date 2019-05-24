#include "ProcessParser.h"

#pragma region Getters
/*
 *
 */
string ProcessParser::getCmd(string pid)
{ 

}

/*
 * Calculate the amount of cpu a given process id is using
 * 
 * @param pid Process id to calculate usage for
 * 
 * @return Percent of usage in string format
 */
string ProcessParser::getCpuPercent(string pid)
{
    string line;
    float result;
    ifstream inputStream;
    vector<string> values;

    // Read data from /proc/$$/stat
    Util::getStream((Path::basePath + pid + "/" + Path::statPath), inputStream);
    // Process data into a vector<string>
    getline(inputStream, line);
    values = SplitString(line);
    
    float utime     = stof(ProcessParser::getProcUpTime(pid));
    float stime     = stof(values[14]);
    float cutime    = stof(values[15]);
    float cstime    = stof(values[16]);
    float startTime = stof(values[21]); 

    float systemUpTime = ProcessParser::getSysUpTime();    
    float frequency  = sysconf(_SC_CLK_TCK);

    float totalTime = utime + stime + cutime + cstime;
    float seconds = systemUpTime - (startTime/frequency);

    result = 100.0 * ((totalTime/frequency)/seconds);

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
 * Gets the amount of time a process has been up in seconds
 * 
 * @param pid Process id to check
 * 
 * @return String representation of number of seconds
 */
string ProcessParser::getProcUpTime(string pid)
{
    string line;
    ifstream inputStream;
    vector<string> values;

    // Read data from /proc/$$/stat
    Util::getStream((Path::basePath + pid + "/" + Path::statPath), inputStream);
    // Process data into a vector<string>
    getline(inputStream, line);
    values = SplitString(line);

    float frequency  = sysconf(_SC_CLK_TCK);

    return to_string(stof(values[13]) / frequency);
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
 * Get total time since system boot in seconds
 * 
 * @return Time since boot in seconds
 */
long ProcessParser::getSysUpTime()
{
    ifstream inputStream;
    string line;
    long result;
    vector<string> values;

    Util::getStream(Path::basePath + Path::upTimePath, inputStream);
    getline(inputStream, line);
    
    // Zero index of /proc/uptime is number of seconds since system boot
    values = SplitString(line);
    result = stol(values[0]);
    
    return result;
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
    string searchTerm = "VmData";

    string line;
    float result;
    vector<string> values;

    // Opening stream for specific file
    ifstream inputStream;
    Util::getStream((Path::basePath + pid + Path::statusPath), inputStream);
    
    // Search line by line for the searchTerm
    while(std::getline(inputStream, line))
    {
        // Check to see if the line starts with searchTerm
        if (line.compare(0, searchTerm.size(),searchTerm) == 0)
        {
            values = SplitString(line);

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

/*
 * Splits a given string on spaces
 * 
 * @param line String to be split
 * 
 * @return Vector of strings
 */
vector<string> ProcessParser::SplitString(string line)
{
    // Use sstream to slice the string and place in a vector
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;

    // Build vector of strings
    vector<string> values(beg, end);
    
    return values;
}