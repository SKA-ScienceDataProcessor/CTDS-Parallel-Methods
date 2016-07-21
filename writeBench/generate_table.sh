#!/bin/bash --login

#OUTPUT="/share/home/ska/output"
OUTPUT="../readBench/data"
#OUTPUT="/scratch2/mwasci/blao/CTDS_data"
mkdir -p $OUTPUT
QUOTA="2000000000"

rows="500"
length="200"

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

RUNLINE="$RUN ./generate_table $rows $length $length TiledShapeStMan $OUTPUT/Table$1"
echo $RUNLINE
$RUNLINE >> log

