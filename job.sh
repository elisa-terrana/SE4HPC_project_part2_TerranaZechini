#!/bin/bash
#SBATCH --job-name=step2TerranaZechini
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --ntasks=2
#SBATCH --time=00:10:00

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

module load singularity

singularity run -c --bind /scratch_local:$TMPDIR Singularity.sif
