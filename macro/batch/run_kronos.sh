#!/bin/bash
#SBATCH -J Flow
#SBATCH -o out/%j.out.log
#SBATCH -e error/%j.err.log
#SBATCH --time=02:00:00
#SBATCH --array=0-199

EXE_DIR=$1
OUT_DIR=$2
FILELIST=$3
CENTRALITY=$4
MIN_STEP=$5
MAX_STEP=$6

INDEX=$(($SLURM_ARRAY_TASK_ID))
INDEX=$(printf "%03d" "$INDEX")

#mkdir -p $OUT_DIR/$INDEX
#cd $OUT_DIR/$INDEX
cd $OUT_DIR

cp $EXE_DIR/main ./
    echo Building Q-vectors:
    for ((i=0; i<=$MAX_STEP; i++))
    do
        INFILE=qn_step_$(($i-1)).root
        echo Step $i...
        ./main correct $FILELIST $INFILE $CENTRALITY &> log_correction_$i.txt
        mv qn.root qn_step_$i.root
        mv output.root output_step_$i.root
    done

    echo Building correlations:
    for ((i=$MIN_STEP; i<=$MAX_STEP; i++))
    do
        echo Step $i...
        IN_FILE=output_step_$i.root
        OUT_FILE=qncorr_$i.root

        ./main analysis $IN_FILE &> log_ana_${i}.txt
        mv corr.root $OUT_FILE
    done

rm main

cd -

echo "Done!"
