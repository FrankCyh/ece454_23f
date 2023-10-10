cd /nfs/ug/homes-2/c/cheny776/ece454/lab2/
gcc 2_2_reduce_mem_ref.c -O0 -o 2_2_reduce_mem_ref
for i in {1..5}; do
    ./2_2_reduce_mem_ref
done