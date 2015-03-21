#!/usr/bin/env bash

while [[ 1 == 1 ]];
do
    ./gen.py > in
    ./sol < in > out1
    ./brute.py < in > out2

    diff --ignore-space-change out1 out2
    if [[ $? != 0 ]];
    then
        echo 'WA'
        exit
    fi
    
    echo 'OK'
done
