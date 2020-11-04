enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(TEST_SRC
    test_MAL.cpp
)

set(TEST_SRC2
    test_ADNode.cpp
)

add_library(MALTest SHARED ${TEST_SRC} ${TEST_H})
add_library(ADNodeTest SHARED ${TEST_SRC2} ${TEST_H})

if(APPLE)
  target_link_libraries(MALTest gtest gtest_main)
  target_link_libraries(ADNodeTest gtest gtest_main)
endif()