obj/SysInfo.o: SysInfo.h SysInfo.cpp obj/ProcessParser.o obj/Util.o
	g++ -c SysInfo.cpp -o obj/SysInfo.o

obj/ProcessParser.o: ProcessParser.h ProcessParser.cpp Constants.h
	g++ -c ProcessParser.cpp -o obj/ProcessParser.o

obj/Util.o: Util.h Util.cpp
	g++ -c Util.cpp -o obj/Util.o

clean:
	rm ./obj/*.o