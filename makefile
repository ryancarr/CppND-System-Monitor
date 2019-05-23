CXX=g++
OBJ = ./obj
BIN = ./bin

$(BIN)/main: main.cpp $(OBJ)/SysInfo.o $(OBJ)/ProcessContainer.o $(OBJ)/*.o
	$(CXX) main.cpp $(OBJ)/SysInfo.o $(OBJ)/ProcessContainer.o -o bin/main

$(OBJ)/ProcessContainer.o: ProcessContainer.h ProcessContainer.cpp $(OBJ)/Process.o $(OBJ)/*.o
	$(CXX) -c ProcessContainer.cpp -o $(OBJ)/ProcessContainer.o

$(OBJ)/Process.o: Process.h Process.cpp $(OBJ)/ProcessParser.o $(OBJ)/*.o
	$(CXX) -c Process.cpp -o $(OBJ)/Process.o

$(OBJ)/SysInfo.o: SysInfo.h SysInfo.cpp $(OBJ)/ProcessParser.o $(OBJ)/Util.o $(OBJ)/*.o
	$(CXX) -c SysInfo.cpp -o $(OBJ)/SysInfo.o

$(OBJ)/ProcessParser.o: ProcessParser.h ProcessParser.cpp $(OBJ)/Constants.o $(OBJ)/*.o
	$(CXX) -c ProcessParser.cpp -o $(OBJ)/ProcessParser.o

$(OBJ)/Constants.o: Constants.h Constants.cpp $(OBJ)/*.o
	$(CXX) -c Constants.cpp -o $(OBJ)/Constants.o

$(OBJ)/Util.o: Util.h Util.cpp $(OBJ)/*.o
	$(CXX) -c Util.cpp -o $(OBJ)/Util.o

$(OBJ)/*.o:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)