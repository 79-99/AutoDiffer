CXXFLAGS=-std=c++14

all: example_autodiffer_scalar.o example_autodiffer_scalar2.o example_adnode_scalar.o example_autodiffer_jacobian.o example_autodiffer_vector.o
	g++ ${CXXFLAGS} example_autodiffer_scalar.o -o example_autodiffer_scalar
	g++ ${CXXFLAGS} example_autodiffer_scalar2.o -o example_autodiffer_scalar2
	g++ ${CXXFLAGS} example_adnode_scalar.o -o example_adnode_scalar
	g++ ${CXXFLAGS} example_autodiffer_jacobian.o -o example_autodiffer_jacobian
	g++ ${CXXFLAGS} example_autodiffer_vector.o -o example_autodiffer_vector

example_autodiffer_scalar.o: example_autodiffer_scalar.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer_scalar.cpp

example_autodiffer_scalar2.o: example_autodiffer_scalar2.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer_scalar2.cpp

example_adnode_scalar.o: example_adnode_scalar.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_adnode_scalar.cpp

example_autodiffer_jacobian.o: example_autodiffer_jacobian.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer_jacobian.cpp


example_autodiffer_vector.o: example_autodiffer_vector.cpp ../AutoDiffer/include/AutoDiffer.hpp
	g++ ${CXXFLAGS} -c example_autodiffer_vector.cpp


clean:
	rm *.o example_autodiffer_scalar example_autodiffer_scalar2 example_adnode_scalar example_autodiffer_jacobian example_autodiffer_vector 
	@echo "  >> Removed *.o files!\n"
