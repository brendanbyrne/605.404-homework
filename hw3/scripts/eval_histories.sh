#!/usr/bin/env bash

PATH=$HOME/Documents/school/605.404-homework/hw3/build:$PATH

runMACD ()
{
    echo $1
    if [-z $1 ];then
        echo "No input given"
    else
        macd -i ../histories/$1
    fi
}

top=$HOME/Documents/school/605.404-homework/hw3
for stock in `ls $top/histories`
do
    path=$top/histories/$stock
    #echo $path
    echo $stock `macd -i $path`
done





