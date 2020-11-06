enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(ADVALUE_TEST_SRC
    test_ADValue.cpp
)

set(ADNODE_TEST_SRC
    test_ADNode.cpp
)

add_library(ADValueTest SHARED ${ADVALUE_TEST_SRC} ${TEST_H})
add_library(ADNodeTest SHARED ${ADNODE_TEST_SRC} ${TEST_H})

if(APPLE)
  target_link_libraries(ADValueTest gtest gtest_main)
  target_link_libraries(ADNodeTest gtest gtest_main)
endif()