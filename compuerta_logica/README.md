### MPI
- `mpicc -o com_log_mpi com_log_mpi.c`
- `mpiexec -n 4 com_log_mpi`

***
### Pthreads
- `gcc -pthread -o com_log_pthreads com_log_pthreads.c`
- `./com_log_pthreads 4`

***
### OpenMP
- `gcc -fopenmp -o com_log_omp com_log_omp.c`
- `./com_log_omp 4`