CXX=g++

bin/main: main.cpp obj/SysInfo.o obj/ProcessContainer.o
	$(CXX) main.cpp obj/SysInfo.o obj/ProcessContainer.o -o bin/main

obj/ProcessContainer.o: ProcessContainer.h ProcessContainer.cpp obj/Process.o
	$(CXX) -c ProcessContainer.cpp -o obj/ProcessContainer.o

obj/Process.o: Process.h Process.cpp obj/ProcessParser.o
	$(CXX) -c Process.cpp -o obj/Process.o

obj/SysInfo.o: SysInfo.h SysInfo.cpp obj/ProcessParser.o obj/Util.o
	$(CXX) -c SysInfo.cpp -o obj/SysInfo.o

obj/ProcessParser.o: ProcessParser.h ProcessParser.cpp obj/Constants.o
	$(CXX) -c ProcessParser.cpp -o obj/ProcessParser.o

obj/Constants.o: Constants.h Constants.cpp
	$(CXX) -c Constants.cpp -o obj/Constants.o

obj/Util.o: Util.h Util.cpp
	$(CXX) -c Util.cpp -o obj/Util.o

clean:
	$(RM) ./obj/*.o
	$(RM) ./bin/*