#!/bin/bash --login

source /home/blao/bashrc_AdiosStMan

tablePath="/scratch/pawsey0129/AdiosStMan/CTDS-Parallel-Methods/readBench/data/"
tablename="Table"


for i in $(seq 1 1)
do
   #aprun -B ./read_benchmark /home/blao/CTDS-Parallel-Methods/readBench/data/  Table1
   #aprun -B ./read_benchmark  /scratch/pawsey0129/AdiosStMan/CTDS-Parallel-Methods/readBench/data/  Table
   RUNLINE="aprun -B ./read_benchmark $tablePath $tablename"
   echo $RUNLINE
   $RUNLINE >> log
done
