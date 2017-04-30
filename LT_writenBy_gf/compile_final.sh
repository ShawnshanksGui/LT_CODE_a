#!/bin/bash

################################################
##############primary edition###################
sed -i '339c get_d(&(ptr_struct_ensym->d), cdf, k);' encode_method.c
sed -i '342c get_index(ptr_struct_ensym->index, ptr_struct_ensym->d, k);' encode_method.c
echo "primary edition!!!!!!!!!!!!!!!!:\n"
echo "primary edition!!!!!!!!!!!!!!!!:\n"
./compile_mix.sh
echo "primary edition!!!!!!!!!!!!!!!!:\n"
echo "                   !!!!!!!!!!               "
################################################


################################################
##############semi-random edition###############
echo "semi-random edition!!!!!!!!!!!!!!:\n"
echo "semi-random edition!!!!!!!!!!!!!!:\n"
sed -i '339c get_d_one(&(ptr_struct_ensym->d));' encode_method.c
sed -i '342c get_index_one(ptr_struct_ensym->index, ptr_struct_ensym->d, k);' encode_method.c
./compile_mix.sh
################################################

