#!/bin/bash

a=0
b=1
temp=0

for i in {1..10}
do
   echo "$a"
   temp=$a
   a=$((a + b))
   b=$temp
done
