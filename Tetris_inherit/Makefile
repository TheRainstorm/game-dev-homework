SrcFiles=$(wildcard src/*.cpp)
ObjFiles=$(patsubst %.cpp, %.o, $(SrcFiles))

CXX = g++
INCLUDE = -I./include
LIB = -lpthread
CXXFLAGS = $(INCLUDE) $(LIB)

tetris: $(ObjFiles)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	@rm $(ObjFiles)
	@rm tetris
	@rm tetris.exe