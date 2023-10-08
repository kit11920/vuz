#!/bin/bash

beg_size=10
end_size=$(( 501 + $beg_size ))
step=100
count=10

rm -rf ./apps/*
rm -rf ./grafics/*
rm -rf ./preproc_data/*

./build_apps.sh $beg_size $end_size $step
./update_data.sh $beg_size $end_size $step $count
./make_preproc.sh $beg_size $end_size $step
./make_postproc.sh


