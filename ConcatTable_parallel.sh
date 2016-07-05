#!/bin/bash

OUTPUT="/share/home/ska/output"
QUOTA="2000000000"

for i in $(seq 1 10)
do
    for rows in $(seq 1000 1000 500000)
    do
      for length in $(seq 9000 1000 9000)
      do
         CHECK=$(du -s $OUTPUT | cut -f1)
            if [ "$CHECK" -gt "$QUOTA" ]; then
                echo "$CHECK bytes in $OUTPUT, reaching disk quota $QUOTA, cleaning up ..."
                rm -rf $OUTPUT/*
            fi

         RUNLINE="mpirun ./ConcatTable_parallel $rows $length $length $OUTPUT/${rows}rows_${length}length_${i}_$1.casa"
         echo $RUNLINE
        $RUNLINE >> log
      done
    done
done
