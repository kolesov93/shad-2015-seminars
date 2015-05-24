#!/usr/bin/env bash

testNo=3
while [[ $testNo -lt 40 ]];
do
    ./gen.py > "$testNo".in
    let 'testNo+=1'
done

