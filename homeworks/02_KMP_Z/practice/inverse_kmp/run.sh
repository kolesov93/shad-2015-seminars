#!/usr/bin/env bash

while [[ 1 ]];
do
    echo 'Generating test'
    ./gen.py > in
    echo 'Running brute'
    ./brute < in
    if [[ $? != 0 ]]; then
        echo 'Brute failed'
        exit 1
    fi
    echo 'Running solution'
    ./sol < in
    if [[ $? != 0 ]]; then
        echo 'Solution failed'
        exit 1
    fi
done
