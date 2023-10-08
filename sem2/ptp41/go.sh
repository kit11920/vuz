#!/bin/bash

new=$1

beg_size=10
end_size=$(( 10001 + $beg_size ))
step=500
count=25


rm -rf ./grafics/*
rm -rf ./preproc_data/*

if [[ $new != "-n" ]]; then
    rm -rf ./apps/*
    ./build_apps.sh $beg_size $end_size $step
fi


./update_data.sh $beg_size $end_size $step $count
./make_preproc.sh $beg_size $end_size $step $count
./make_postproc.sh 

python3 ./make_tabs.py 
./make_tab_rse.sh $beg_size $end_size $step

