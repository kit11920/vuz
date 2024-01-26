#!/bin/bash

date +"%T.%N" > log.txt
./app.exe >> log.txt
date +"%T.%N" >> log.txt
