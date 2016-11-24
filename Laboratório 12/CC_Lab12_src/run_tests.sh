#!/bin/bash

DATA=/home/zambon/Teaching/2016-2/CC/laboratorio/tests/
IN=$DATA/in
OUT=$DATA/out12

EXE=./tmsim

for infile in `ls $IN/*.tm`; do
    base=$(basename $infile)
    outfile=$OUT/${base/.tm/.out}
    $EXE < $infile > $outfile
done
