#!/bin/sh

COUNTER=0
PORT=$1
MAX=$2
while [ $COUNTER  -lt $MAX ]; do
    let COUNTER=COUNTER+1

    # Use a 0 timeout to force multiple simultaneous connexions to UDP socket
    echo 'date' | nc -uw 0 localhost $PORT
    echo 'time' | nc -uw 0  localhost $PORT
    echo 'datetime' | nc -uw 0  localhost $PORT
done
