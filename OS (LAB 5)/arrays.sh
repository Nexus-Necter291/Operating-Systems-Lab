#!/bin/bash

declare -A matrix

rows=4
cols=4

for ((i=0;i<rows;i++))
do
	for ((j=0;j<cols;j++))
	do
		matrix[$i,$j]=$RANDOM
	done
done

for ((i=0;i<rows;i++))
do
	for((j=0;j<cols;j++))
	do
		echo ${matrix[$i,$j]}
	done
done

f1="%$((${#rows}+1))s"
f2="%9s"

printf "$f1" ' '
for ((i=0;i<rows;i++))
do
	printf "$f2" $i
done
echo

for ((i=0;i<rows;i++))
do
	printf "$f1" $j
	for ((j=0;j<cols;j++))
	do
		printf "$f2" ${matrix[$i,$j]}  
	done
	echo
done