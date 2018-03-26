#!/bin/bash
#SBATCH -J QnCorr
#SBATCH -o out/%j.out.log
#SBATCH -e error/%j.err.log
#SBATCH --time=02:20:00
#SBATCH --array=0-18

NEVENTS=1000000
ENERGY=13
SRC_DIR=/lustre/nyx/cbm/users/klochkov/FlowAnalysis/Macro/
INPUT_DIR=/lustre/nyx/cbm/users/klochkov/FlowAnalysis/Input/qn_tree_13gev/

SHIFT=2619
# 26194-26376   13 AGeV
# 26615-2688    30 AGeV

source /lustre/nyx/cbm/users/klochkov/cbmroot/20170611/install/bin/CbmRootConfig.sh
export DISPLAY=localhost:0.0

ONE=1
SLURM_INDEX=`expr $SLURM_ARRAY_TASK_ID + $ONE`
INDEX=$(($SLURM_ARRAY_TASK_ID + $SHIFT))

INPUTFILE=$INPUT_DIR/qntree_$INDEX
OUTDIR=/lustre/nyx/cbm/users/klochkov/FlowAnalysis/batch/13gev/$INDEX/

mkdir -p $OUTDIR
root -l -b -q $SRC_DIR/rootlogon.C "$SRC_DIR/RunInterface.C(\"$INPUTFILE\", \"$OUTDIR\", $NEVENTS )"
