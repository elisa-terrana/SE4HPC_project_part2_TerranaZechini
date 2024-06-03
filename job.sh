#!/bin/bash
#SBATCH --job-name=step2TerranaZechini
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --ntasks 2
#SBATCH --time=00:20:00

module load singularity

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

singularity run --bind /scratch_local:$TMPDIR Singularity.sif