#!/usr/bin/env bash

testNo=1
while [[ $testNo -lt 40 ]];
do
    ./gen.py > "$testNo".in
    let 'testNo+=1'
done

