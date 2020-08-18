# !/bin/sh

export LIBDIR=/usr/lib
export INCDIR=/usr/include

# compile userspace API library
echo "------------------------------------- Compiling user space library -------------------------------------"
cmake .
make clean
make

# Copy library and header files to local machine
echo "Copying header files to: $INCDIR"
#sudo cp tpt.h /usr/include
#sudo cp mdom.h /usr/include
#sudo cp kernel_api.h /usr/include

echo "Copying sbox library to: $LIBDIR"
#sudo cp sbox.so /usr/lib
#sudo cp sbox.so /usr/lib/x86_64-linux-gnu/
#sudo cp sbox.so /lib/x86_64-linux-gnu/

echo "------------------------------------- Installation copmleted -------------------------------------"
