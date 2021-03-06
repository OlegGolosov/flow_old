#!/bin/bash

STEP=$1

#LOG_DIR=/lustre/nyx/cbm/users/$USER/log
MY_PATH=/lustre/nyx/cbm/users/ogolosov
#ROOT_PATH=/lustre/nyx/cbm/users/klochkov/soft/root6/root-6.10.08/build/bin/thisroot.sh
#ROOT_PATH=/home/ogolosov/root6/bin/thisroot.sh
#MY_PATH=/home/ogolosov/Desktop/analysis
BATCH_DIR=$MY_PATH/flow/macro/batch
LOG_DIR=$MY_PATH/NA49_flow/log
EXE_DIR=$MY_PATH/flow/build
CENTRALITY=$MY_PATH/tpc_centr.root
FLOW_DIR=$MY_PATH/NA49_flow
#FILE_LIST=$MY_PATH/NA49_data/fileList.txt
FILE_LISTS=$MY_PATH/NA49_data/fileLists/40_all
#FILE_LISTS=$MY_PATH/NA49_data/fileLists/40_central
#FILE_LISTS=$MY_PATH/NA49_data/fileLists/40_minbias
#FILE_LISTS=$MY_PATH/NA49_data/fileLists/debug


FLOW_DIR=$FLOW_DIR/lowY/piminus1
NJOBS=50
MIN_STEP=1
MAX_STEP=2
#PART=main
#TIME=0:01:00
PART=debug
TIME=0:20:00


#if [ $# == 0 ];then
#	echo input number of step!
#	exit
#fi

for FILE_LIST in $FILE_LISTS/*
do
  OUT_DIR=$FLOW_DIR/$(basename "$FILE_LIST")
	echo $FILE_LIST
	echo $OUT_DIR

  #source $ROOT_PATH

  mkdir -p $OUT_DIR
  mkdir -p $LOG_DIR
  mkdir -p $LOG_DIR/out
  mkdir -p $LOG_DIR/error
	
  split -n l/$NJOBS -d -a 3 $FILE_LIST $OUT_DIR/$(basename "$FILE_LIST")_

  sbatch --partition $PART --time=$TIME --array=0-$(expr $NJOBS - 1) -D $LOG_DIR --export=ALL $BATCH_DIR/run_kronos.sh $EXE_DIR $OUT_DIR $FILE_LIST $CENTRALITY $MIN_STEP $MAX_STEP $BATCH_DIR $STEP

#  . $BATCH_DIR/run_kronos.sh $EXE_DIR $OUT_DIR $FILE_LIST $CENTRALITY $MIN_STEP $MAX_STEP $BATCH_DIR

#  sbatch --partition main -D "/lustre/nyx/cbm/users/$USER/log" --export=ALL run_qa.sh na61
done
