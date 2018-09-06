#!/bin/sh

COUNTER=0
MAX=$1
while [ $COUNTER  -lt $MAX ]; do
    let COUNTER=COUNTER+1

    echo 'date' | nc -uw 0 localhost 5060
    echo 'time' | nc -uw 0  localhost 5060
    echo 'datetime' | nc -uw 0  localhost 5060
done
