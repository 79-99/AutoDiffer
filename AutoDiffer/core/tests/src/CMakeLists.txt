enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(ALL_TEST_SRC
	test_ADNode.cpp
	test_ADValue.cpp
	test_Parser.cpp
	test_AutoDiffer_vector.cpp
	test_AutoDiffer_correctness.cpp
	test_AutoDiffer_multithread.cpp
	test_AutoDiffer_invalid.cpp
)

add_library(AllTest SHARED ${ALL_TEST_SRC} ${TEST_H})

OPTION(THREAD "Link against openmp" OFF)
if(THREAD)
	find_package(OpenMP REQUIRED)
	target_link_libraries(AllTest OpenMP::OpenMP_CXX)
	target_compile_definitions(AllTest PUBLIC USE_THREAD)
endif()

if(APPLE)
  target_link_libraries(AllTest gtest gtest_main)
endif()