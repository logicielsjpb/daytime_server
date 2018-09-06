#!/bin/sh

COUNTER=0
PORT=$1
MAX=$2
while [  $COUNTER -lt $MAX ]; do
    let COUNTER=COUNTER+1

    echo 'date\ntime\ndatetime' | nc -w 0 localhost $PORT
done
