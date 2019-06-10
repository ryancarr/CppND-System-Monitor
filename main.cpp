#include <chrono>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

#include "ProcessContainer.h"
#include "SysInfo.h"


/*
 * Convert a string to a C string
 * 
 * @param string The string you'd like to convert
 * 
 * @return C String version of your string
 */
char* getCString(string str)
{
    char * cstr = new char [str.length()+1];
    strcpy (cstr, str.c_str());
    return cstr;
}

/*
 * The main draw method for the program
 * 
 * @param SysInfo The sysinfo object to use for this session
 * 
 * @param WINDOW* A pointer to the system window
 */
void writeSysInfoToConsole(SysInfo sys, WINDOW* sys_win)
{
    sys.setAttributes();

    mvwprintw(sys_win,2,2,getCString(( "OS: " + sys.getOSName())));
    mvwprintw(sys_win,3,2,getCString(( "Kernel version: " + sys.getKernelVersion())));
    mvwprintw(sys_win,4,2,getCString( "CPU:    "));
    wattron(sys_win,COLOR_PAIR(1));
    wprintw(sys_win,getCString(Util::getProgressBar(sys.getCpuPercent())));
    wattroff(sys_win,COLOR_PAIR(1));
    mvwprintw(sys_win,5,2,getCString(( "Other cores: ")));
    wattron(sys_win,COLOR_PAIR(1));
    vector<string> val = sys.getCoresStats();
    
    for(int i=0;i<val.size();i++)
    {
     mvwprintw(sys_win,(6+i),2,getCString(val[i]));
    }

    wattroff(sys_win,COLOR_PAIR(1));
    mvwprintw(sys_win,10,2,getCString(( "Memory: ")));
    wattron(sys_win,COLOR_PAIR(1));
    wprintw(sys_win,getCString(Util::getProgressBar(sys.getMemPercent())));
    wattroff(sys_win,COLOR_PAIR(1));
    mvwprintw(sys_win,11,2,getCString(( "Total Processes:" + sys.getTotalProc())));
    mvwprintw(sys_win,12,2,getCString(( "Running Processes:" + sys.getRunningProc())));
    mvwprintw(sys_win,13,2,getCString(( "Up Time: " + Util::convertToTime(sys.getUpTime()))));
    wrefresh(sys_win);
}

/*
 * A helper draw method that updates the process section of the screen
 * 
 * @param vector A vector of all the currently running processes
 * 
 * @param WINDOW* A pointer to the system window
 */
void getProcessListToConsole(vector<string> processes, WINDOW* win)
{

    wattron(win,COLOR_PAIR(2));
    mvwprintw(win,1,2,"PID:");
    mvwprintw(win,1,11,"User:");
    mvwprintw(win,1,21,"CPU[%%]:");
    mvwprintw(win,1,32,"RAM[MB]:");
    mvwprintw(win,1,42,"Uptime:");
    mvwprintw(win,1,55,"CMD:");
    wattroff(win, COLOR_PAIR(2));
    
    for(int i=0; i< processes.size();i++)
    {
        mvwprintw(win,2+i,2,getCString(processes[i]));
    }
}

/*
 * The main draw loop that calls the appropriate draw method
 * 
 * @param SysInfo The SysInfo object for this session
 * 
 * @param ProcessContainer The ProcessContainer object for this sesssion
 */
void printMain(SysInfo sys,ProcessContainer procs)
{
	initscr();			/* Start curses mode 		  */
    noecho(); // not printing input values
    cbreak(); // Terminating on classic ctrl + c
    start_color(); // Enabling color change of text
    int yMax,xMax;
    getmaxyx(stdscr,yMax,xMax); // getting size of window measured in lines and columns(column one char length)
	WINDOW *sys_win = newwin(17,xMax-1,0,0);
	WINDOW *proc_win = newwin(15,xMax-1,18,0);


    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    int counter = 0;
    
    while(1)
    {
        box(sys_win,0,0);
        box (proc_win,0,0);
        procs.refreshList();
        vector<vector<string>> processes = procs.getList();
        writeSysInfoToConsole(sys, sys_win);
        getProcessListToConsole(processes[counter], proc_win);
        wrefresh(sys_win);
        wrefresh(proc_win);
        refresh();
        sleep(1);
        
        if(counter ==  (processes.size() -1))
            counter = 0;
        else 
            counter++;
    }

	endwin();
}

/*
 * Main entry point of the program
 */
int main(int argc, char *argv[])
{
    //Object which contains list of current processes, Container for Process Class
    ProcessContainer procs;
    
    // Object which containts relevant methods and attributes regarding system details
    SysInfo sys;
    
    //string s = writeToConsole(sys);
    printMain(sys,procs);
    
    return 0;
}