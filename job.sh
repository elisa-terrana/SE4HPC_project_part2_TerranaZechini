#!/bin/bash
#SBATCH --job-name=step2TerranaZechini
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --ntasks 2
#SBATCH --time=00:20:00

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

singularity exec -c --bind /scratch_local:$TMPDIR Singularity.sif