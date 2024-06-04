#!/bin/bash
#SBATCH --job-name=step2TerranaZechini1
#SBATCH --output=output1.txt
#SBATCH --error=error1.txt
#SBATCH --ntasks=2
#SBATCH --time=00:05:00

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

export SINGULARITY_BINDPATH=/opt/build

singularity run -c --bind /scratch_local:$TMPDIR Singularity1.sif