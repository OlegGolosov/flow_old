#!/bin/bash
#SBATCH -J Flow
#SBATCH -o out/%j.out.log
#SBATCH -e error/%j.err.log
#SBATCH --time=00:20:00
#SBATCH --array=50-199

SETUP=$1

INDEX=$(($SLURM_ARRAY_TASK_ID))
INDEX=$(printf "%03d" "$INDEX")

EXE_DIR=/lustre/nyx/cbm/users/klochkov/soft/flow/build/
OUT_DIR=/lustre/nyx/cbm/users/klochkov/data/flow_output/na61/pbpb30/16_00_7_8/qa
FILELIST=/lustre/nyx/cbm/users/klochkov/na61/data/pbpb30/datatree/16_007_newdatatree/filelist/filelist_$INDEX

source /lustre/nyx/cbm/users/klochkov/soft/root6/root-6.10.08/build/bin/thisroot.sh

mkdir -p $OUT_DIR/$INDEX
cd $OUT_DIR/$INDEX
cp $EXE_DIR/qa ./

./qa $FILELIST $SETUP &> log_qa_$INDEX.txt

rm qa


echo "DONE"
