# CMake generated Testfile for 
# Source directory: /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests
# Build directory: /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ADValueTest.Unit.Test "/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/bin/ADValueTest.Unit.Test")
set_tests_properties(ADValueTest.Unit.Test PROPERTIES  _BACKTRACE_TRIPLES "/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/CMakeLists.txt;32;add_test;/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/CMakeLists.txt;0;")
add_test(ADNodeTest.Unit.Test "/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/bin/ADNodeTest.Unit.Test")
set_tests_properties(ADNodeTest.Unit.Test PROPERTIES  _BACKTRACE_TRIPLES "/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/CMakeLists.txt;35;add_test;/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/CMakeLists.txt;0;")
subdirs("src")
