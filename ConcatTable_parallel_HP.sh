#!/bin/bash

nn=35
    bsub -J test$nn -q astron -n $nn -R span[ptile=1] -o test -x ./parallel_array_write_hp_test.sh $nn

for nn in $(seq 34 -1 16)
do
   mm=$(($nn+1))
#   echo $mm
   bsub -J test$nn -q astron -n $nn -w "done("test$mm")" -R span[ptile=1] -o test -x ./parallel_array_write_hp_test.sh $nn
done

