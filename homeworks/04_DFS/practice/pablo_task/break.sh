#!/usr/bin/env bash

testNo=0
record=0
while [[ 1 ]];
do
    let 'testNo+=1'
    echo '************* Test' $testNo '*************'   
    echo 'Generating test'
    ./mgen.py > in

    echo 'Solving test'
    ./bad < in > out 2> iterations.txt
    echo 'Cheking test'
    ./checker in out out
    if [[ $? != 0 ]];
    then
        echo 'WA'
        exit
    fi

    iterations=$(<iterations.txt) 
    echo Got result of $iterations iterations \(record is $record\)
    if [[ $iterations -gt $record ]];
    then
        record=$iterations
        echo Set new record $record
        cp in record.in
    fi
done
