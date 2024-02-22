#!/bin/bash

if [ -w $file ]
then
	echo "File has write permission"
else
	echo "File does not have write permission"
fi

if [ -x $file ]
then
	echo "File has execute permission"
else 
	echo "File does not have execute permission"
fi
