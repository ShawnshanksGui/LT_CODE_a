#!/bin/bash

#######################semi-random edition######################
echo "semi-random edition!!!!!!!!!!!!!!:\n"
echo "semi-random edition!!!!!!!!!!!!!!:\n"
sed -i '339c get_d_one(&(ptr_struct_ensym->d));' encode_method.c
sed -i '342c get_index_one(ptr_struct_ensym->index, ptr_struct_ensym->d, k);' encode_method.c

sed -i '30c #define MAX_INDEX_LIST 120' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 200' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 240' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 320' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test

sed -i '30c #define MAX_INDEX_LIST 400' construct_method.h
gcc -g -o test main.c encode_method.c decode_method.c trans_over_ch.c -lm
./test
