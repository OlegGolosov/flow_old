#!/bin/bash

INDIR=$1
MERGE=$2

. set_path.sh

for (( step=1; step<=2; step++ ))
do  
	if [ $MERGE != 0 ]; then
		hadd -f $INDIR/corr_$step.root $INDIR/*/corr_$step.root
	fi
	root -q ../../rootlogon.C '../save_graphs.C ("'$INDIR/corr_$step.root'","'$INDIR/graph_$step.root'")'
done

if [ $MERGE != 0 ]; then
	hadd -f $INDIR/qa.root $INDIR/*/qa.root
fi
root -q -b '../draw_graphs.C ("'$INDIR'")'