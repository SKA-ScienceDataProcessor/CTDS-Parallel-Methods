#!/bin/bash --login

source /home/blao/bashrc_AdiosStMan

tablePath="/scratch/pawsey0129/AdiosStMan/data1/"
tablename="Table"
#tablename="Table0"

for i in $(seq 1 1)
do
   RUNLINE="aprun -B ./read_benchmark $tablePath $tablename"
   #RUNLINE="aprun -B ./read_benchmark $tablePath $tablePath$tablename"
   echo $RUNLINE
   $RUNLINE >> log
done
