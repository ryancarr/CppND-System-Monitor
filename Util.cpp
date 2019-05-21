#include "Util.h"

/*
 * Converts a specified number of seconds into hours : minutes : seconds
 * 
 * @param input_seconds Starting number of seconds to convert
 * 
 * @return A string representing hh:mm:ss
 */
string Util::convertToTime (long int input_seconds)
{
    long minutes = input_seconds / 60;
    long hours = minutes / 60;
    long seconds = int(input_seconds%60);
    minutes = int(minutes%60);
    string result = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
    return result;
}

/*
 * Brings in a percent and returns a string representing a progress bar filled to that amount
 * 
 * @param percent The percent that is to be represented by a progress bar
 * 
 * @return A string of characters representing an ASCII progress bar
 */
string Util::getProgressBar(string percent)
{
    // constructing string for given percentage
    // 50 bars is uniformly stretched 0 - 100 %
    // meaning: every 2% is one bar(|)

    string result = "0%% ";
    int _size= 50;
    int  boundaries;
    try
    {
        boundaries = (stof(percent)/100)*_size;
    } catch (...)
    {
        boundaries = 0;
    }

    for(int i=0;i<_size;i++)
    {
        if(i<=boundaries)
            result +="|";
        else
            result +=" ";
    }

    result +=" " + percent.substr(0,5) + " /100%%";
    return result;
}

/*
 * Opens an input file stream and performs basic error checking
 * 
 * @param path Absolute path to file to open
 * 
 * @param stream If successful a reference to the stream is created
 */
void Util::getStream(string path, ifstream& stream)
{
    stream.open (path, ifstream::in);
    if (!stream && !stream.is_open())
    {
        stream.close();
        throw runtime_error("Non - existing PID");
    }
}