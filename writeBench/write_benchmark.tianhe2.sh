#!/bin/bash 

for i in $(seq 500 -100 100)
do
        yhbatch -N $i -n $i --dependency=singleton write_benchmark.sh $i $i
done

for i in $(seq 90 -10 10)
do
        yhbatch -N $i -n $i --dependency=singleton write_benchmark.sh $i $i
done




