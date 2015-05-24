#!/usr/bin/env bash

testNo=0
while [[ 1 ]];
do
    let 'testNo+=1'
    echo '************* Test' $testNo '*************'   
    echo 'Generating test'
    ./gen.py > in
    echo 'Validating test'
    ./validator < in
    if [[ $? != 0 ]];
    then
        echo 'Test is not valid'
        exit
    fi

    echo 'Solving test'
    ./sol < in > out
    echo 'Bruting test'
    ./brute < in > rout
    diff out rout
    if [[ $? != 0 ]];
    then
        echo 'WA'
        exit
    fi
done
