#!/bin/sh 

#for i in $(seq 10 -10 10)
#do
#	sbatch --account=$IVEC_PROJECT --time=12:00:00 --nodes=$i --ntasks-per-node=1  --dependency=singleton parallel_array_write.sh
#done

for i in $(seq 10 -1 10)
do
        sbatch --account=$IVEC_PROJECT --time=00:10:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton read_benchmark.sh 
done




