SrcFiles=$(wildcard src/*.cpp)
ObjFiles=$(patsubst %.cpp, %.o, $(SrcFiles))

CXX = g++
INCLUDE = -I./include
LIB = -lpthread
CXXFLAGS = $(INCLUDE) $(LIB)

tetris: $(ObjFiles)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/graph.o: src/graph.cpp include/defines.h
	$(CXX) $(INCLUDE) -c -o $@ $<
src/Tetris.o: src/Tetris.cpp include/defines.h
	$(CXX) $(INCLUDE) -c -o $@ $<
src/main.o: src/main.cpp include/defines.h
	$(CXX) $(INCLUDE) -c -o $@ $<

#if don't support ANSI Escape codes on windows
cscrutil: $(ObjFiles) ./cscrutil/src/scrutil.o
	$(CXX) $(CXXFLAGS) -o tetris $^

./cscrutil/src/scrutil.o: ./cscrutil/src/scrutil.c ./cscrutil/src/scrutil.h
	$(CXX) -c -o $@ $<

clean:
	@rm $(ObjFiles)
	@rm tetris