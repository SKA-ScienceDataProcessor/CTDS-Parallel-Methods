#!/bin/sh 

#for i in $(seq 500 -100 100)
#do
#	sbatch --account=$IVEC_PROJECT --time=12:00:00 --nodes=$i --ntasks-per-node=1  --dependency=singleton write_benchmark.sh
#done

for i in $(seq 500 -1 500)
do
	sbatch --account=$IVEC_PROJECT --time=10:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton write_benchmark.sh
        #sbatch --account=$IVEC_PROJECT --time=00:10:00 --nodes=1 --ntasks-per-node=1 --dependency=singleton generate_table.sh $i 
done




