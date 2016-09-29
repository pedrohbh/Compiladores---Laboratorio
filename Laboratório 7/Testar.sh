#!/bin/bash

clear
clear
make

for d in ../../lab02/in/* ; do
    e=$(echo "$d" | awk -F '/' '{print $5}')
    s=$(echo "$e" | awk -F '.' '{print $1}')
    #echo $e
    ./parser < $d > teste.out
    diff out/$s.out teste.out > testeDiff.out
    if [ -s testeDiff.out ]
    then
        echo "NAO FUNFOU - " $d
        cat testeDiff.out
    else
        echo "FUNFOU - " $d
    fi
done

make clean

