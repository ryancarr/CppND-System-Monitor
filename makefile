CXX=g++
OBJ = ./obj
BIN = ./bin

$(BIN)/main: main.cpp $(OBJ)/SysInfo.o $(OBJ)/ProcessContainer.o $(OBJ)/*.o
	$(CXX) -std=c++17 main.cpp $(OBJ)/SysInfo.o $(OBJ)/ProcessContainer.o -o $(BIN)/main -lcurses

$(OBJ)/ProcessContainer.o: ProcessContainer.h ProcessContainer.cpp $(OBJ)/Process.o $(OBJ)/*.o
	$(CXX) -std=c++17 ProcessContainer.cpp $(OBJ)/Process.o -o $(OBJ)/ProcessContainer.o

$(OBJ)/Process.o: Process.h Process.cpp $(OBJ)/ProcessParser.o $(OBJ)/*.o
	$(CXX) -std=c++17 Process.cpp $(OBJ)/ProcessParser.o -o $(OBJ)/Process.o

$(OBJ)/SysInfo.o: SysInfo.h SysInfo.cpp $(OBJ)/ProcessParser.o $(OBJ)/*.o
	$(CXX) -std=c++17 SysInfo.cpp $(OBJ)/ProcessParser.o -o $(OBJ)/SysInfo.o

$(OBJ)/ProcessParser.o: ProcessParser.h ProcessParser.cpp $(OBJ)/Constants.o $(OBJ)/Util.o $(OBJ)/*.o
	$(CXX) -std=c++17 ProcessParser.cpp $(OBJ)/Constants.o $(OBJ)/Util.o -o $(OBJ)/ProcessParser.o

$(OBJ)/Constants.o: Constants.h Constants.cpp $(OBJ)/*.o
	$(CXX) -std=c++17 Constants.cpp -o $(OBJ)/Constants.o

$(OBJ)/Util.o: Util.h Util.cpp $(OBJ)/*.o
	$(CXX) -std=c++17 Util.cpp -o $(OBJ)/Util.o

$(OBJ)/*.o:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)