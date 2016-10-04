#!/bin/sh 

for i in $(seq 100 -10 10)
do
        sbatch --account=$IVEC_PROJECT --time=10:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton read_benchmark.sh
done

for i in $(seq 9 -1 1)
do
        sbatch --account=$IVEC_PROJECT --time=10:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton read_benchmark.sh 
done




