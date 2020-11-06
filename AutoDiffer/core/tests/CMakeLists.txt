enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

find_library(gtest      NAMES gtest      gtestd      HINTS "${gtest_dir}/lib")
find_library(gtest_main NAMES gtest_main gtest_maind HINTS "${gtest_dir}/lib")

set(ADVALUE_TEST_EXE ADValueTest.Unit.Test)
set(ADNODE_TEST_EXE ADNodeTest.Unit.Test)
set(TEST_SRC_PATH src)

# include test headers
include_directories(src)

set(libs
    ${gtest} ${gtest_main}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_subdirectory(${TEST_SRC_PATH})

add_executable(${ADVALUE_TEST_EXE} test_main.cpp)
target_link_libraries(${ADVALUE_TEST_EXE} ADValueTest ADNodeTest AutoDiffer ${libs})
target_link_libraries(${ADVALUE_TEST_EXE} pthread)

add_executable(${ADNODE_TEST_EXE} test_main.cpp)
target_link_libraries(${ADNODE_TEST_EXE} ADNodeTest ADValueTest AutoDiffer ${libs})
target_link_libraries(${ADNODE_TEST_EXE} pthread)

add_test(NAME ${ADVALUE_TEST_EXE}
         COMMAND $<TARGET_FILE:${ADVALUE_TEST_EXE}>)

add_test(NAME ${ADNODE_TEST_EXE}
         COMMAND $<TARGET_FILE:${ADNODE_TEST_EXE}>)

add_custom_command(
   TARGET ${ADVALUE_TEST_EXE}
   COMMENT "Run ADValue Unit Tests"
   POST_BUILD
   COMMAND ${ADVALUE_TEST_EXE}
)

add_custom_command(
   TARGET ${ADNODE_TEST_EXE}
   COMMENT "Run ADNode Unit Tests"
   POST_BUILD
   COMMAND ${ADNODE_TEST_EXE}
)
