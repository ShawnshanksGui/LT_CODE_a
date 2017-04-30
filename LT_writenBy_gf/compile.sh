#!/bin/bash


rm hello.txt
touch hello.txt
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
