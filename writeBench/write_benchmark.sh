#!/bin/bash --login

#OUTPUT="/share/home/ska/output"
OUTPUT="/scratch/pawsey0129/AdiosStMan/data1"
#OUTPUT="/scratch2/mwasci/blao/CTDS_data"
QUOTA="5000000000"

for i in $(seq 1 1)
do
    for rows in $(seq 1000 200 1000)
    do
      for length in $(seq 9000 1000 9000)
      do
         CHECK=$(du -s $OUTPUT | cut -f1)
            if [ "$CHECK" -gt "$QUOTA" ]; then
                echo "$CHECK bytes in $OUTPUT, reaching disk quota $QUOTA, cleaning up ..."
                rm -rf $OUTPUT/*
            fi

            if [ "$VENDOR" == "cray" ]; then
               # NP=$(wc -l $PBS_NODEFILE | awk '{print $1}')
               # RUN="aprun -n$(( $NP / 16  )) -N1"
                RUN="aprun -B"
            else
                RUN="mpirun"
            fi 
 
#         RUNLINE="$RUN ./write_benchmark $rows $length $length $OUTPUT/${rows}rows_${length}length_${i}.casa TiledShapeStMan"
         RUNLINE="$RUN ./write_benchmark $rows $length $length $OUTPUT/${rows}rows_${length}length_${i}.casa StandardStMan"
         echo $RUNLINE
         $RUNLINE >> log
      done
    done
done
