#!/bin/bash

touch infile.txt
echo $(printf "%19891s" 'a') > infile.txt
echo "1" >> infile.txt
time ./a.out < infile.txt
rm infile.txt
