#!/usr/bin/env bash

testNo=0
while read p; do
    let 'testNo += 1'
    echo $p | ./gen.py > in$testNo
done < lengths.txt
