# SE4HPCproject

### Step 2 - From build to release and manual job execution

* **Automating the build, test and release processes**: the CI/CD pipeline can be found in .github/workflows/matrix_mult.yml

* **Containerizing the application**: our singularity container descriptor is located in Singularity.def and the extended version of the action is in .github/workflows/matrix_mult_singularity.yml, we would like to note that in the previous action cmake was configured and called explicitly, while in this one we're doing it implicitly within the definition file.

* **Executing on the cluster**: the relevant files are job.sh, output.txt and error.txt, during this step we manually transfer to the cluster the .sh file and the Singularity.sif container through the scp command and then execute with "sbatch job.sh" within the cluster.

---
### Step 3 - Automating a job submission with containerization

* The extended version of the action, in which we completely automate the process, is located in .github/workflows/matrix_mult_singularity.yml, in particular the last 7 steps are in charge of transferring files with scp to the cluster, running the job and retrieving the output from the cluster.