#!/bin/bash
kill -STOP 9543
make;
export GOMP_CPU_AFFINITY="0-55"
export OMP_NUM_THREADS=56
export OMP_SCHEDULE=dynamic,4096

array[0]=0

for i in 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do 
    array[i]=$((2**$i))
done 


# page rank
for i in 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do
    for N in 0 1 2 3 4 5 6 7 8 9
    do
        echo "----------------Iteration " $N "-----------------"
        echo "Shell passed r =" ${array[i]} 
        echo "./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 11 -o ./del1/ -r" ${array[i]}
        ./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 11 -o ./del1/ -r ${array[i]}
        sleep 10
    done
    sleep 10
done

# BFS
for i in  0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do
    for N in 0 1 2 3 4 5 6 7 
    do
        echo "----------------Iteration " $N "-----------------"
        echo "Shell passed r =" ${array[i]} 
        echo "./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 10 -o ./del1/ -r" ${array[i]}
        ./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 10 -o ./del1/ -r ${array[i]}
        sleep 10
    done
    sleep 10
done

# 1 hop queries
for i in 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do
    for N in 0 1 2 3 4 5
    do
        echo "----------------Iteration " $N "-----------------"
        echo "Shell passed r =" ${array[i]} 
        echo "./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 11 -o ./del1/ -r" ${array[i]}
        ./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 12 -o ./del1/ -r ${array[i]}
        sleep 10
    done
    sleep 10
done

## 2 hop queries
#for i in 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
#do
#    for N in 0 1 2 3 4 5
#    do
#        echo "----------------Iteration " $N "-----------------"
#        echo "Shell passed r =" ${array[i]} 
#        echo "./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 11 -o ./del1/ -r" ${array[i]}
#        ./grdf -i /mnt/disk_huge_1/pradeepk/pradeep_graph/kron_28_16/ -c 3 -j 13 -o ./del1/ -r ${array[i]}
#        sleep 10
#    done
#    sleep 10
#done
#

kill -CONT 9543
