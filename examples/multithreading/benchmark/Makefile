CXXFLAGS=-std=c++14

all: example_std_thread.o example_openmp.o
	g++ ${CXXFLAGS} example_std_thread.o -o example_std_thread
	g++ ${CXXFLAGS} -Xpreprocessor -fopenmp -lomp example_openmp.o -o example_openmp
	
example_std_thread.o: example_std_thread.cpp ../../../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_std_thread.cpp

example_openmp.o: example_openmp.cpp ../../../AutoDiffer/include_examples/AutoDiffer.hpp
	g++ ${CXXFLAGS} -Xpreprocessor -fopenmp -c example_openmp.cpp

clean:
	rm *.o example_std_thread example_openmp
	@echo "  >> Removed *.o files!\n"
