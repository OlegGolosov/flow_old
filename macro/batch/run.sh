#!/bin/bash

#LOGDIR=/lustre/nyx/cbm/users/$USER/log
#MYPATH=/lustre/nyx/cbm/users/ogolosov
#ROOT_PATH=/lustre/nyx/cbm/users/klochkov/soft/root6/root-6.10.08/build/bin/thisroot.sh
#ROOT_PATH=/home/ogolosov/root6/bin/thisroot.sh
MYPATH=/home/ogolosov/Desktop/Analysis
LOGDIR=$MYPATH/Lucas_flow/log
EXE_DIR=$MYPATH/Lucas_flow/build
OUT_DIR=$MYPATH/NA49_flow
FILELIST=$MYPATH/NA49fileList.txt
#OUT_DIR=$MYPATH/NA61_flow
#FILELIST=$MYPATH/NA61fileList.txt
CENTRALITY=$MYPATH/tpc_centr.root
MIN_STEP=1
MAX_STEP=1

#split -n l/10 -d -a 3 filelist.txt filelist_

#source $ROOT_PATH

mkdir -p $OUT_DIR
mkdir -p $LOGDIR
mkdir -p $LOGDIR/out
mkdir -p $LOGDIR/error

#sbatch --partition main -D $LOGDIR --export=ALL run_kronos.sh $EXE_DIR $OUT_DIR $FILELIST $CENTRALITY $MAX_STEP

. run_kronos.sh $EXE_DIR $OUT_DIR $FILELIST $CENTRALITY $MIN_STEP $MAX_STEP

# sbatch --partition main -D "/lustre/nyx/cbm/users/$USER/log" --export=ALL run_qa.sh na61
