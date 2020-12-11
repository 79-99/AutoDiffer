CXXFLAGS=-std=c++14

all: example_live_demo.o
	g++ ${CXXFLAGS} example_live_demo.o -o example_live_demo
	
example_live_demo.o: example_live_demo.cpp ../../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_live_demo.cpp

clean:
	rm *.o example_live_demo
	@echo "  >> Removed *.o files!\n"
