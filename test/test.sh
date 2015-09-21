#!/bin/bash

set -e # exit on error

SRT_VTT=$1
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

if [ -d "$DIR/output" ]; then
  rm -rf $DIR/output/*
else
  mkdir $DIR/output
fi

echo
echo BASIC
$SRT_VTT -o $DIR/output/basic $DIR/input
$SRT_VTT -v -o $DIR/output/basic $DIR/input
$SRT_VTT -q -o $DIR/output/basic $DIR/input
diff -r $DIR/output/basic $DIR/expected/basic

echo
echo RECURSIVE
$SRT_VTT -r -o $DIR/output/recursive $DIR/input
diff -r $DIR/output/recursive $DIR/expected/recursive

echo
echo TIMING
$SRT_VTT -t 100 -o $DIR/output/timing $DIR/input/subs1.srt
$SRT_VTT -t -1053 -o $DIR/output/timing $DIR/input/subs2.srt
diff -r $DIR/output/timing $DIR/expected/timing

rm -rf $DIR/output

echo
echo PASSED
