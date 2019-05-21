CXX=g++

obj/SysInfo.o: SysInfo.h SysInfo.cpp obj/ProcessParser.o obj/Util.o
	$(CXX) -c SysInfo.cpp -o obj/SysInfo.o

obj/ProcessParser.o: ProcessParser.h ProcessParser.cpp Constants.h
	$(CXX) -c ProcessParser.cpp -o obj/ProcessParser.o

obj/Util.o: Util.h Util.cpp
	$(CXX) -c Util.cpp -o obj/Util.o

clean:
	$(RM) ./obj/*.o