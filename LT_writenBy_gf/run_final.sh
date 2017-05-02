#!/bin/bash

################################################
##############primary edition###################
sed -i '339c get_d(&(ptr_struct_ensym->d), cdf, k);' encode_method.c
sed -i '342c get_index(ptr_struct_ensym->index, ptr_struct_ensym->d, k);' encode_method.c
echo "primary edition!!!!!!!!!!!!!!!!:" >> result.txt
echo "primary edition!!!!!!!!!!!!!!!!:\n"
./run_mix.sh
echo "primary edition!!!!!!!!!!!!!!!!:\n"
echo "                   !!!!!!!!!!               "
################################################


################################################
##############semi-random edition###############
echo "semi-random edition!!!!!!!!!!!!!!:" >> result.txt
echo "semi-random edition!!!!!!!!!!!!!!:\n"
sed -i '339c get_d_one(&(ptr_struct_ensym->d));' encode_method.c
sed -i '342c get_index_one(ptr_struct_ensym->index, ptr_struct_ensym->d, k);' encode_method.c
./run_mix.sh
################################################

