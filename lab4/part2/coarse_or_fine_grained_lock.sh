echo -e "Coarse-grained lock"
for i in {1..5}
do
    ./coarse_or_fine_grained_lock 0
    echo "-------------------"
done

echo -e "\n\nFine-grained lock"
for i in {1..5}
do
    ./coarse_or_fine_grained_lock 1
    echo "-------------------"
done