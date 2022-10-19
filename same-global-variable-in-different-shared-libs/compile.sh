set -e

rm -rf *.o

# common
g++ -g -fPIC -c -o common.o common.cpp
ar -crs libcommon.a common.o

# a.so
g++ -g -shared -fPIC -o liba.so a.cpp -Wl,--whole-archive libcommon.a -Wl,--no-whole-archive

# b.so
g++ -g -shared -fPIC -o libb.so b.cpp -Wl,--whole-archive libcommon.a -Wl,--no-whole-archive

# main
g++ -g main.cpp -L. -Wl,-rpath=. -la -lb -o main