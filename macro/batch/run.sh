#!/bin/bash

#LOG_DIR=/lustre/nyx/cbm/users/$USER/log
MY_PATH=/lustre/nyx/cbm/users/ogolosov
#ROOT_PATH=/lustre/nyx/cbm/users/klochkov/soft/root6/root-6.10.08/build/bin/thisroot.sh
#ROOT_PATH=/home/ogolosov/root6/bin/thisroot.sh
#MY_PATH=/home/ogolosov/Desktop/analysis
BATCH_DIR=$MY_PATH/flow/macro/batch
LOG_DIR=$MY_PATH/NA49_flow/log
EXE_DIR=$MY_PATH/flow/build
#FILE_LIST=$MY_PATH/NA49_data/fileList.txt
#FILE_LIST=/lustre/nyx/cbm/users/ogolosov/NA49_data/fileLists/40GeV-minbias.list
CENTRALITY=$MY_PATH/tpc_centr.root
FLOW_DIR=$MY_PATH/NA49_flow

OUT_DIR=$FLOW_DIR/new/pimin

#OUT_DIR=$OUT_DIR/01D
#FILE_LIST=/lustre/nyx/cbm/users/ogolosov/NA49_data/fileLists/1_4std--40GeV-minbias-01D.list

OUT_DIR=$OUT_DIR/02C
FILE_LIST=/lustre/nyx/cbm/users/ogolosov/NA49_data/fileLists/1_4std+-40GeV-minbias-02C.list

MIN_STEP=1
MAX_STEP=2

#split -n l/10 -d -a 3 filelist.txt filelist_

#source $ROOT_PATH

mkdir -p $OUT_DIR
mkdir -p $LOG_DIR
mkdir -p $LOG_DIR/out
mkdir -p $LOG_DIR/error

sbatch --partition main -D $LOG_DIR --export=ALL $BATCH_DIR/run_kronos.sh $EXE_DIR $OUT_DIR $FILE_LIST $CENTRALITY $MIN_STEP $MAX_STEP $BATCH_DIR

#. $BATCH_DIR/run_kronos.sh $EXE_DIR $OUT_DIR $FILE_LIST $CENTRALITY $MIN_STEP $MAX_STEP $BATCH_DIR

# sbatch --partition main -D "/lustre/nyx/cbm/users/$USER/log" --export=ALL run_qa.sh na61
