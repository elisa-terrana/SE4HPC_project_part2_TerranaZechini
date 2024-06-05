#!/bin/bash
#SBATCH --job-name=step2TerranaZechini1
#SBATCH --output=output1.txt
#SBATCH --error=error1.txt
#SBATCH --ntasks=2
#SBATCH --time=00:05:00

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

module load singularity
module load openmpi

mpirun -n 2 singularity exec -c --bind /scratch_local:$TMPDIR Singularity1.sif /opt/build/main