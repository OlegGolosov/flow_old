#!/bin/bash
#SBATCH -J Flow
#SBATCH -o out/%j.out.log
#SBATCH -e error/%j.err.log
#SBATCH --time=02:00:00
#SBATCH --array=0-199

EXE_DIR=$1
OUT_DIR=$2
FILE_LIST=$3
CENTRALITY=$4
MIN_STEP=$5
MAX_STEP=$6
BATCH_DIR=$7

INDEX=$(($SLURM_ARRAY_TASK_ID))
INDEX=$(printf "%03d" "$INDEX")

#mkdir -p $OUT_DIR/$INDEX
#cd $OUT_DIR/$INDEX
cd $OUT_DIR

cp $EXE_DIR/main ./
    echo Building Q-vectors:
    for ((i=0; i<=$MAX_STEP; i++))
    do
        CALIB=calib_$(($i-1)).root
        echo Step $i...
        ./main correct $FILE_LIST $CALIB $CENTRALITY &> log_qn_$i.txt
        mv calib.root calib_$i.root
        mv qn.root qn_$i.root
    done

    echo Building correlations:
    for ((i=$MIN_STEP; i<=$MAX_STEP; i++))
    do
        echo Step $i...
        QN_FILE=qn_$i.root
        CORR_FILE=corr_$i.root

#        ./main analysis $QN_FILE &> log_corr_${i}.txt
        mv corr.root $CORR_FILE
    done

rm main

    echo Saving graphs:
    cd $EXE_DIR/..
    for ((i=$MIN_STEP; i<=$MAX_STEP; i++))
    do
        echo Step $i...
        CORR_FILE=$OUT_DIR/corr_$i.root
        GRAPH_FILE=$OUT_DIR/graph_$i.root
        LOG_FILE=$OUT_DIR/log_graph_$i.log
#        root -b -l -q 'macro/save_profiles.C ("'$CORR_FILE'","'$GRAPH_FILE'")' &> $LOG_FILE
    done

cd $BATCH_DIR

echo "Done!"
