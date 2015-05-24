#!/usr/bin/env bash

testNo=3
while [[ $testNo -lt 20 ]];
do
    ./gen.py > "$testNo".in
    let 'testNo+=1'
done

