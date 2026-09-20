#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP_SIZE 1024 // SIMD vector width strip size 

int main() {
    double *A = (double*)malloc(N * sizeof(double));
    double *B = (double*)malloc(N * sizeof(double));
    double *C = (double*)malloc(N * sizeof(double));
    
    // Arrays initialize 
    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0;
        B[i] = i * 2.0;
    }

    double tstart, tstop, tcalc;
    tstart = omp_get_wtime();

    // OpenMP parallel strip mining
    #pragma omp parallel for
    for (int i = 0; i < N; i += STRIP_SIZE) {
        int limit = (i + STRIP_SIZE < N) ? (i + STRIP_SIZE) : N;
        for (int j = i; j < limit; j++) {
            C[j] = A[j] * B[j];
        }
    }

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Array multiplication completed successfully.\n");
    printf("Time taken = %f seconds\n", tcalc);

    free(A);
    free(B);
    free(C);
    return 0;
}
