CXXFLAGS=-std=c++14

all: example_autodiffer1.o example_autodiffer2.o example_adnode1.o example_autodiffer_jacobian.o
	g++ ${CXXFLAGS} example_autodiffer1.o -o example_autodiffer1
	g++ ${CXXFLAGS} example_autodiffer2.o -o example_autodiffer2
	g++ ${CXXFLAGS} example_adnode1.o -o example_adnode1
	g++ ${CXXFLAGS} example_autodiffer_jacobian.o -o example_autodiffer_jacobian

example_autodiffer1.o: example_autodiffer1.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer1.cpp

example_autodiffer2.o: example_autodiffer2.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer2.cpp

example_adnode1.o: example_adnode1.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_adnode1.cpp

example_autodiffer_jacobian.o: example_autodiffer_jacobian.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer_jacobian.cpp


clean:
	rm *.o example_autodiffer1 example_autodiffer2 example_adnode1 example_autodiffer_jacobian
	@echo "  >> Removed *.o files!\n"
