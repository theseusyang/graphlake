#!/bin/bash
make;
export GOMP_CPU_AFFINITY="0-55"
export OMP_NUM_THREADS=56
export OMP_SCHEDULE=dynamic,4096

array[0]=0

for i in 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do 
    array[i]=$((2**$i))
done 



# 2 hop queries
for i in 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do
    for N in 0 1 2 3 4 5 6
    do
        echo "----------------Iteration " $N "-----------------"
        echo "Shell passed r =" ${array[i]} 
        echo "./graphone32 -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 13 -o ./del1/ -r" ${array[i]} -v 268435456  
        ./graphone32 -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 13 -o ./del1/ -r ${array[i]} -v 268435456  
        sleep 10
    done
done
