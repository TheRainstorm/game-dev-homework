SrcFiles=$(wildcard src/*.cpp)
ObjFiles=$(patsubst %.cpp, %.o, $(SrcFiles))

CXX = g++
INCLUDE = -I./include
LIB = -lpthread
CXXFLAGS = $(INCLUDE) $(LIB)

tetris: $(ObjFiles)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/graph.o: graph.c define.h
	$(CXX) -c -o $@ $<
src/Tetris.o: Tetris.c define.h
	$(CXX) -c -o $@ $<
src/main.o: main.c define.h
	$(CXX) -c -o $@ $<

#if don't support ANSI Escape codes on windows
cscrutil: $(ObjFiles) ./cscrutil/src/scrutil.o
	$(CXX) $(CXXFLAGS) -o tetris $^

./cscrutil/src/scrutil.o: ./cscrutil/src/scrutil.c ./cscrutil/src/scrutil.h
	$(CXX) -c -o $@ $<

clean:
	@rm $(ObjFiles)
	@rm tetris