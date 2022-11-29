#!/bin/bash

c++ -Wall -I. `root-config --cflags` -o main *.cc `root-config --libs`