CXXFLAGS=-std=c++14

all: example_autodiffer1.o example_autodiffer2.o example_adnode1.o example_autodiffer_vector.o
	g++ ${CXXFLAGS} example_autodiffer1.o -o example_autodiffer1
	g++ ${CXXFLAGS} example_autodiffer2.o -o example_autodiffer2
	g++ ${CXXFLAGS} example_adnode1.o -o example_adnode1
	g++ ${CXXFLAGS} example_autodiffer_vector.o -o example_autodiffer_vector

example_autodiffer1.o: example_autodiffer1.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer1.cpp

example_autodiffer2.o: example_autodiffer2.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer2.cpp

example_adnode1.o: example_adnode1.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_adnode1.cpp

example_autodiffer_vector.o: example_autodiffer_vector.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer_vector.cpp


clean:
	rm *.o example_autodiffer1 example_autodiffer2 example_adnode1 example_autodiffer_vector
	@echo "  >> Removed *.o files!\n"
