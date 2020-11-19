CXXFLAGS=-std=c++14

all: example.o
	g++ ${CXXFLAGS} example.o -o example

example.o: example.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example.cpp

clean:
	rm *.o example
	@echo "  >> Removed *.o files!\n"
