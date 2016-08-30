#!/bin/bash --login

for i in $(seq 1 10)
do
   #aprun -B ./read_benchmark /home/blao/CTDS-Parallel-Methods/readBench/data/  Table1
   aprun -B ./read_benchmark
done
