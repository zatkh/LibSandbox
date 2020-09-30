# !/bin/sh

# compile userspace API library
echo "------------------------------------- Compiling user space library -------------------------------------"
mkdir -p out
cd out
cmake ../
make clean
make
