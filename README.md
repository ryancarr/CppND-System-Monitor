# CppND-System-Monitor

This is a basic process manager similar to htop. Due to the way that this project was designed it requires Linux to run because it gathers information from the procfs. Windows and MacOS both lack this folder structure.

## To setup and compile in Ubuntu:

1. Clone repository
```
git clone https://github.com/ryancarr/CppND-System-Monitor
```

3. Install `ncurses` package
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
4. Compile and run
```
g++ -std=c++17 main.cpp Util.cpp Constants.cpp SysInfo.cpp ProcessParser.cpp Process.cpp ProcessContainer.cpp -o main -lcurses
./main
```
