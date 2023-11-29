set -x

rm -rf *.txt
g++ generate_files.cpp
./a.out
g++ map-reduce.cpp
./a.out
