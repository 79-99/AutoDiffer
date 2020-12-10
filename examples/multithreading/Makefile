CXXFLAGS=-std=c++14

all: example_multiple_functions.o
	g++ ${CXXFLAGS} example_multiple_functions.o -o example_multiple_functions
	
example_multiple_functions.o: example_multiple_functions.cpp ../../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_multiple_functions.cpp

clean:
	rm *.o example_multiple_functions
	@echo "  >> Removed *.o files!\n"
