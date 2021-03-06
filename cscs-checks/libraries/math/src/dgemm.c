#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

extern void dgemm_(char*, char*, int*, int*, int*, double*, double*,
                   int*, double*, int*, double*, double*, int*);

int main(int argc, char* argv[])
{
    double alpha = 1.2;
    double beta = 1.0e-3;
    double gflop;
    double time_avg;

    int m = 1024;
    int n = 2048;
    int k = 512;
    int LOOP_COUNT = 10;
    int i;

    char ta='N';
    char tb='N';

    struct timeval start_time, end_time, duration[LOOP_COUNT];
    
    if (argc >= 2) m = atoi(argv[1]);
    if (argc >= 3) n = atoi(argv[2]);
    if (argc >= 4) k = atoi(argv[3]);
    if (argc >= 5) LOOP_COUNT = atoi(argv[4]);

    double perf[LOOP_COUNT];
    double time[LOOP_COUNT];
    double* A = (double*)malloc(sizeof(double)*m*k);
    double* B = (double*)malloc(sizeof(double)*k*n);
    double* C = (double*)malloc(sizeof(double)*m*n);

    printf("Size of Matrix A(mxk)\t\t:\t%d x %d\n", m, k);
    printf("Size of Matrix B(kxn)\t\t:\t%d x %d\n", k, n);
    printf("Size of Matrix C(mxn)\t\t:\t%d x %d\n", m, n);
    printf("LOOP COUNT\t\t\t:\t%d \n", LOOP_COUNT);
    printf("\n");

    for (i=0; i<m*k ; ++i) A[i] = i%3+1;
    for (i=0; i<k*n ; ++i) B[i] = i%3+1;
    for (i=0; i<m*n ; ++i) C[i] = i%3+1;

    gflop = (2.0 * m * n * k + 3.0 * m * n) * 1E-9;

    /* CALL DGEMM ONCE TO INITIALIZE THREAD/BUFFER */
    dgemm_(&ta, &tb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);
    
    /* LOOP OVER DGEMM IN ORDER TO SMOOTHEN THE RESULTS */
    for (i=0; i<LOOP_COUNT; ++i)
    {
        gettimeofday(&start_time, NULL);
        dgemm_(&ta, &tb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);
        gettimeofday(&end_time,NULL);
        timersub(&end_time, &start_time, &duration[i]);
    }
    
    for (i=0; i<LOOP_COUNT; ++i)
    {
        time[i] = (duration[i].tv_sec * 1.e3 + 
                   duration[i].tv_usec * 1.e-3) * 1.e-3;
        perf[i] = gflop / time[i];
        time_avg += time[i];
        printf("Run %d \t\t\t\t:\t%.5f GFlops/sec\n", i, perf[i]);
    }

    printf("\n");
    printf("Flops based on given dimensions\t:\t%.5f GFlops/sec\n", gflop);
    printf("Avg. time / DGEMM operation\t:\t%f secs \n", time_avg/LOOP_COUNT);
    printf("Time for %d DGEMM operations\t:\t%f secs \n", LOOP_COUNT, time_avg);
    printf("\n");

    return 0;
}
