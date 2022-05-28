### MPI
- `mpicc -o crib_erato_mpi crib_erato_mpi.c`
- `mpiexec -n 4 crib_erato_mpi`

***
### Pthreads
- `gcc -pthread -o crib_erato_pthreads crib_erato_pthreads.c -lm`
- `./crib_erato_pthreads 4`

***
### OpenMP
- `gcc -fopenmp -o crib_erato_omp crib_erato_omp.c -lm`
- `./crib_erato_omp 4`