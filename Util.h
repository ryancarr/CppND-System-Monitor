#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <string>

using std::ifstream;
using std::string;
using std::to_string;
using std::runtime_error;

// Classic helper function
class Util 
{
    public:
        static string convertToTime ( long int);
        static string getProgressBar(string);
        static void getStream(string, ifstream&);
};

#endif // UTIL_H