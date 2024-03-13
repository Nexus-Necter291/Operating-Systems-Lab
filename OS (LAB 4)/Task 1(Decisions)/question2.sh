#!/bin/bash
day=$(date +%A)
case $day in
    Monday)
        echo "Have a productive Monday!"
        ;;
    Tuesday)
        echo "Keep up the good work on Tuesday!"
        ;;
    Wednesday)
        echo "Happy Wednesday!"
        ;;
    Thursday)
        echo "Hang in there, it's almost Friday!"
        ;;
    Friday)
        echo "Blessed Friday!"
        ;;
    Saturday)
        echo "Enjoy your weekend!"
        ;;
    Sunday)
        echo "Relax and recharge on Sunday!"
        ;;
    *)
        echo "Not sure what day it is today!"
        ;;
esac
