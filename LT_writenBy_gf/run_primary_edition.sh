#!/bin/bash

################priamry edition##################
sed -i '339c get_d(&(ptr_struct_ensym->d), cdf, k);' encode_method.c
sed -i '342c get_index(ptr_struct_ensym->index, ptr_struct_ensym->d, k);' encode_method.c
echo "primary edition!!!!!!!!!!!!!!!!:" >> "result.txt" #record the result 
echo "primary edition!!!!!!!!!!!!!!!!:"                 #display in the screen

sed -i '30c #define MAX_INDEX_LIST 40' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 80' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 88' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 96' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 120' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test
################################################
