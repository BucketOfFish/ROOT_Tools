#!/bin/bash
COUNT=1
while [ $COUNT -lt 8 ]; do
	mkdir $COUNT/
	for ((i=$COUNT*15-14; i<=$COUNT*15; i++)); do
		mv *`printf %06d $i`* $COUNT/
	done
	let COUNT=$COUNT+1
done

COUNT=1
while [ $COUNT -lt 8 ]; do
	hadd $COUNT.root $COUNT/*
	let COUNT=$COUNT+1
done
