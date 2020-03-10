SrcFiles=$(wildcard *.cpp)
ObjFiles=$(patsubst %.cpp, %.o, $(SrcFiles))

CXX = g++
INCLUDE = -I../include
LIB = -lpthread
CXXFLAGS = $(INCLUDE) $(LIB)

../tetris: $(ObjFiles)
	$(CXX) $(CXXFLAGS) -o  $@ $^

clean:
	rm *.o
	rm ../*.exe

# g++ -I