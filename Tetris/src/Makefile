SrcFiles=$(wildcard *.cpp)
ObjFiles=$(patsubst %.cpp, %.o, $(SrcFiles))

CXX = g++
INCLUDE = -I../include -I../include/pthread
LIB = ../libpthreadGC2.a
CXXFLAGS = $(INCLUDE) $(LIB)

../tetris: $(ObjFiles)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm *.o
	rm ../*.exe