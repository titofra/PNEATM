cmake -G "MinGW Makefiles" -B "./build" -DX64_BITS=ON .
cd build
make
cp ./libpneatm.a ../lib/PNEATM/libpneatm.a
cd ..
