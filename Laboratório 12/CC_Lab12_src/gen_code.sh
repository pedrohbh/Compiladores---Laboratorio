#!/bin/bash

DATA=/home/zambon/Teaching/2016-2/CC/laboratorio/tests/
IN=$DATA/in
OUT=$DATA/out12

EXE=./tinyc

for infile in `ls $IN/*.tny`; do
    base=$(basename $infile)
    outfile=$OUT/${base/.tny/.tm}
    $EXE < $infile > $outfile
done
