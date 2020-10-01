#!/bin/bash
g++ -fprofile-arcs -ftest-coverage src/demo.cc -o bin/demo.out
mv demo.gcno src/
