enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(ALL_TEST_SRC
    test_ALL.cpp
)

add_library(AllTest SHARED ${ALL_TEST_SRC} ${TEST_H})

if(APPLE)
  target_link_libraries(AllTest gtest gtest_main)
endif()