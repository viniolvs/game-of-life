#!/bin/bash

for gen in 100 1000 5000; do
    for size in $(seq 500 500 5000); do
        ./newentry $size $gen > input_${size}_${gen}.in
    done
done

for gen in 100 1000 5000; do
    for size in 10 100; do
        ./newentry $size $gen > input_${size}_${gen}.in
    done
done
