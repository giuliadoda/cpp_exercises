#!/bin/bash

rm -f main
c++ -std=c++11 -Wall -I. `root-config --cflags` -o main *.cc `root-config --libs`