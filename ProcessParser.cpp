#include "ProcessParser.h"

#pragma region Getters
/*
 * Gets the full path location for the given Process ID
 * 
 * @return String containing a path
 */
string ProcessParser::getCmd(string pid)
{
    string line;
    ifstream inputStream;

    Util::getStream((Path::basePath + pid + Path::cmdPath), inputStream);
    getline(inputStream, line);

    return line;
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
 * Get the number of cores your CPU has
 * 
 * @return Int representing the number of CPU cores
 */
int ProcessParser::getNumberOfCores()
{
    /*
    string searchTerm = "processor";

    string line;
    ifstream inputStream;
    vector<string> values;

    Util::getStream(Path::basePath + "cpuinfo", inputStream);

    while(getline(inputStream, line))
    {
        if(line.compare(0, searchTerm.size(), searchTerm) == 0)
            values = SplitString(line);
    }

    return stoi(values[2]) + 1;
    */

   // This method gets the number of logical cores in your computer
   // Also it only takes a fraction of the time that the above commented code does
   return std::thread::hardware_concurrency();
}

/*
 * Gets the number of prcesses that are actively running
 * 
 * @return An integer representing the number of active processes
 */
int ProcessParser::getNumberOfRunningProcesses()
{
    ifstream inputStream;
    string line;
    int result;
    string searchTerm = "procs_running";

    Util::getStream(Path::basePath + Path::statPath, inputStream);

    while(getline(inputStream, line))
    {
        if(line.compare(0, searchTerm.size(), searchTerm) == 0)
        {
            result = stoi(SplitString(line)[1]);
            break;
        }
    }

    return result;
}

/*
 * Gets the name and version of the OS
 * 
 * @return String containing the pretty version of the OS name and version
 */
string ProcessParser::getOSName()
{
    ifstream inputStream;
    string line;
    string searchTerm = "PRETTY_NAME";

    Util::getStream("/etc/os-release", inputStream);

    while(getline(inputStream, line))
    {
        if(line.compare(0, searchTerm.size(), searchTerm) == 0)
            return SplitString(line, "\"")[1];
    }

    return "";
}

/*
 * Get a list of every currently running PID
 * 
 * @return A vector containing every valid PID
 */
vector<string> ProcessParser::getPidList()
{
    DIR *directory = nullptr;
    directory = opendir("/proc");
    vector<string> pids;

    // TODO: if(directory == nullptr) some sort of graceful error

    // Check each entry in directory
    while(dirent *dir = readdir(directory))
    {
        // Default to a PID not being valid
        bool validPid = false;

        // Skip any entries that aren't a directory
        if(dir->d_type != DT_DIR) continue;
        
        // Check each character in dictionary name for digit status
        for(char c : dir->d_name)
        {
            // d_name always contains 256 characters
            // The valid characters are null delimited
            if(c == '\0') break;

            validPid = isdigit(c);

            // Stop checking invalid directories as soon as possible
            if(!validPid) break;
        }

        if(validPid)
            pids.push_back(dir->d_name);
    }

    // Close directory - TODO: Some sort of error checking
    closedir(directory);

    return pids;
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
    float result;
    vector<string> values;

    // Read data from /proc/$$/stat
    Util::getStream((Path::basePath + pid + "/" + Path::statPath), inputStream);
    // Process data into a vector<string>
    getline(inputStream, line);
    values = SplitString(line);

    float frequency  = sysconf(_SC_CLK_TCK);

    result = stof(values[13]) / frequency;

    return to_string(result);
}

/*
 * Find the username of the owner of a given Process ID
 * 
 * @param pid Process ID to check
 * 
 * @return Username if found, blank string if not found
 */
string ProcessParser::getProcUser(string pid)
{
    // Declaring search attribute for file
    string searchTerm = "Uid:";

    ifstream inputStream;
    string line;
    string result;
    vector<string> values;

    // Opening stream for specific file
    Util::getStream((Path::basePath + pid + Path::statusPath), inputStream);
    
    // Search line by line for the searchTerm
    while(std::getline(inputStream, line))
    {
        // Check to see if the line starts with searchTerm
        if (line.compare(0, searchTerm.size(),searchTerm) == 0)
        {
            result = SplitString(line)[1];            
            break;
        }
    }

    // Check /etc/passwd for user name
    Util::getStream("/etc/passwd", inputStream);
    // Search line by line for the searchTerm
    while(std::getline(inputStream, line))
    {
        // Check to see if the line contains the Uid
        if (line.find("x:" + result) != string::npos)
            result = line.substr(0, line.find(":"));
        else
            result = "";
        
    }

    return result;
}

/*
 * Removes idle time from vector of CPU time
 * 
 * @param values A vector of strings generated by getSysCpuPercent()
 * 
 * @return float representing total time spent active
 */
float ProcessParser::getSysActiveCpuTime(vector<string> values)
{
    return (stof(values[S_USER]) +
            stof(values[S_NICE]) +
            stof(values[S_SYSTEM]) +
            stof(values[S_IRQ]) +
            stof(values[S_SOFTIRQ]) +
            stof(values[S_STEAL]) +
            stof(values[S_GUEST]) +
            stof(values[S_GUEST_NICE]));
}

/*
 * Gets total CPU usage for a specific core, if no core is passed in than total usage will be calculated
 * 
 * @param coreNumber Optional variable containing a number representing one of the cpu cores
 * 
 * @return A vector of strings containing data about CPU usage
 */
vector<string> ProcessParser::getSysCpuPercent(string coreNumber = "")
{
    ifstream inputStream;
    string line;
    string searchTerm = "cpu" + coreNumber;
    vector<string> values;

    Util::getStream(Path::basePath + "/" + Path::statPath, inputStream);

    while(getline(inputStream, line))
    {
        if(line.compare(0, searchTerm.size(), searchTerm) == 0)
        {
            values = SplitString(line);
            break;
        }
    }

    return values;
}

/*
 * Removes active time from vector of CPU time
 * 
 * @param values A vector of strings generated by getSysCpuPercent()
 * 
 * @return float representing total time spent idle
 */
float ProcessParser::getSysIdleCpuTime(vector<string> values)
{
    return (stof(values[S_IDLE]) + stof(values[S_IOWAIT]));
}

/*
 * Retrieves the current kernel version
 * 
 * @return A string representing the kernel version number
 */
string ProcessParser::getSysKernelVersion()
{
    ifstream inputStream;
    string line;
    string searchTerm = "Linux version";

    Util::getStream(Path::basePath + Path::versionPath, inputStream);

    while(getline(inputStream, line))
    {
        if(line.compare(0, searchTerm.size(), searchTerm) == 0)
            return SplitString(line)[2];
    }

    return "";
}

/*
 * Calculate the amount of RAM currently available for use
 * 
 * @return Float representing the percent
 */
float ProcessParser::getSysRamPercent()
{
    ifstream inputStream;
    inputStream.open("/proc/meminfo");
    string line;
    unordered_map<string, float> values = { {"MemAvailable:",0},
                                            {"MemFree:", 0},
                                            {"Buffers:", 0} };

    while(getline(inputStream, line))
    {
        // Counter is used to bail out of the file once we've read the data we need
        static int counter = 1;

        // Foreach key,value pair in values unordered_map
        for(auto &kv : values)
        {
            // If the value of kv.second has changed we know we can skip it
            if(kv.second > 0) continue;

            // kv.first refers to the key
            if(line.compare(0, kv.first.size(), kv.first) == 0)
            {
                // kv.second refers to the value
                kv.second = stof(SplitString(line)[1]);
            }

        }

        // Buffer: is on the 4th line, break if we've passed all the lines we want
        if(counter >= 4) break;
        
        counter++;
    }

    // Convert (Free memory / (Total Memory - Buffers)) to a percent representing amount of memory free for use
    return float(100.0 * (1 - values.at("MemFree:") / (values.at("MemAvailable:") - values.at("Buffers:"))));
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
 * Get the number of currently running processes
 * 
 * @return An int representing the number of active processes
 */
int ProcessParser::getTotalNumberOfProcesses()
{
    ifstream inputStream;
    string line;
    int result;
    string searchTerm = "processes";

    Util::getStream(Path::basePath + Path::statPath, inputStream);

    while(getline(inputStream, line))
    {
        if(line.compare(0, searchTerm.size(), searchTerm) == 0)
        {
            result = stoi(SplitString(line)[1]);
            break;
        }
    }

    return result;
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
    // Using slightly modified code provided by the lecture
    
    // Declaring search attribute for file
    string searchTerm = "VmData";

    ifstream inputStream;
    string line;
    float result;
    vector<string> values;

    // Opening stream for specific file
    Util::getStream((Path::basePath + pid + Path::statusPath), inputStream);
    
    // Search line by line for the searchTerm
    while(std::getline(inputStream, line))
    {
        // Check to see if the line starts with searchTerm
        if (line.compare(0, searchTerm.size(),searchTerm) == 0)
        {
            values = SplitString(line);

            // Conversion kB -> MB
            result = (stof(values[1])/float(1024));
            break;
        }
    }
    return to_string(result);
}
#pragma endregion

/*
 * Calculate percent of cput time spent actively working
 * 
 * @param values1 A vector of strings retrieved from getSysCpuPercent
 * 
 * @param values2 A vector of strings retrieved from getSysCpuPercent shortly after values1
 * 
 * @return A string containing a percent from 0 to 100
 */
string ProcessParser::CalculateCpuStats(vector<string> values1, vector<string> values2)
{
    // Method was originally called PrintCpuStats, but that's not an accurate description
    // We're calculating what percent of total runtime has been spent actively working
    
    float activeTime = getSysActiveCpuTime(values2) - getSysActiveCpuTime(values1);
    float idleTime = getSysIdleCpuTime(values2) - getSysIdleCpuTime(values1);
    
    float totalTime = activeTime + idleTime;

    // Returns a float between 0 and 100 representing how busy CPU is
    float result = 100.0F * (activeTime / totalTime);

    return to_string(result);
}

/*
 * Check if a pid actually exists
 * 
 * @return True if pid is found false if it is not found
 */
bool ProcessParser::isPidExisting(string pid)
{
    vector<string> pidList = getPidList();

    // Search pidList for pid, if it exists return true
    return find(pidList.begin(), pidList.end(), pid) != pidList.end();
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
    istringstream buffer(line);
    istream_iterator<string> begin(buffer), end;
    // Build vector of strings
    vector<string> values(begin, end);

    return values;
}

/*
 * Splits a given string on spaces
 *
 * @param line String to be split
 *
 * @param delimiter What to split the string on, if no value passed, split on space
 *
 * @return Vector of strings
 */
vector<string> ProcessParser::SplitString(string line, string delimiter)
{
    size_t position = 0;
    string token;
    vector<string> values;

    while ((position = line.find(delimiter)) != string::npos)
    {
        token = line.substr(0, position);
        values.push_back(token);
        line.erase(0, position + delimiter.length());
    }

    if(line.size() > 0)
        values.push_back(line);

    return values;
}