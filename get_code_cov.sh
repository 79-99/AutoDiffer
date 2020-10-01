#!/bin/bash
for filename in `find . | egrep '\.cc'`;
do
  gcov-5 -n -o . $filename > /dev/null;
done
