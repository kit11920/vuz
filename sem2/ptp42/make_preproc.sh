#!/bin/bash


col=100
beg_size=10
end_size=$(( 5001 + $beg_size ))
step=100

if [ -n "$1" ]; then
    beg_size=$1
fi
if [ -n "$2" ]; then
    end_size=$2
fi
if [ -n "$3" ]; then
    step=$3
fi

opts="O0 Os O3"
cachs="ch nch"



for opt in $opts; do
    for cach in $cachs; do

        sum=0
        count=0

        echo "# rows mid_time" >> "./preproc_data/preproc_"$opt"_"$cach".txt"

        for row in $(seq "$beg_size" "$step" "$end_size" ); do
            echo -n -e "prep $opt $cach  $col x $row \r"

            while read time; do
                sum=$(( $sum + $time ))
                count=$(( $count + 1 ))
            done < "./data/data_"$opt"_"$cach"_"$col"x"$row".txt"

            mid=$(( $sum / $count ))

            echo "$row $mid" >> "./preproc_data/preproc_"$opt"_"$cach".txt"
        done
        
    done
done


