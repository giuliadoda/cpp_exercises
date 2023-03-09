#!/bin/bash

rm -f main
c++ -Wall -std=c++11 -I ../../corsocxx `root-config --cflags` -o main *.cc `root-config --libs`