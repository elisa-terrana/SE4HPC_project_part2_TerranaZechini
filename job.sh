#!/bin/bash
#SBATCH -A <account>
#SBATCH --job-name=step2TerranaZechini
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --time=00:10:00

module load singularity

# ci va srun?
singularity run Singularity.sif /opt/main
