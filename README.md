# CppND-System-Monitor

Starter code for System Monitor Project in the C++ OOP course. Most of the code is provided for you here. Follow along with the classroom lesson to fill out the `ProcessParser` and `Process` classes to complete your project!

## To setup and compile in Udacity Ubuntu workspace:

1. Clone repository into `/home/workspace/`
```
cd /home/workspace/
git clone https://github.com/ryancarr/CppND-System-Monitor
```
2. Follow along with the lesson and make sure you complete the `ProcessParser` and `Process` classes before attempting to run the project.

3. Install `ncurses` package
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
4. Compile and run
```
g++ -std=c++17 main.cpp Util.cpp Constants.cpp SysInfo.cpp ProcessParser.cpp Process.cpp ProcessContainer.cpp -o main -lcurses
./main
```
