/**Matrix multiplication using openMp*/

/**Matrix multiplication sing p threads*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>
     
#define a 100
#define b 100
#define c 100

int main() 
{
    int A[a][b] = {0} ;
    int B[b][c] = {0}  ;
    int C[a][c]={0};
    srand(time(NULL));

    //populate the matrices wiht random values
    for (int i= 0; i< a; i++) {
        for (int j= 0; j< c; j++) {
           int x= rand()%10; //to keep number sin the matrix smaller than 10
           A[i][j]=x;
           x=rand()%10;
           B[i][j]=x;
        }
    }

    double start, end;
    double time_ellapsed;
    start = omp_get_wtime();
    omp_set_num_threads(1);


    int i, j ,k;
    #pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < a; ++i) { //for every row of A
        for (j = 0; j < c; ++j) { //for every column of B
            for (k = 0; k < b; ++k) { //for k (0-> shared dimension)
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = omp_get_wtime();;
    time_ellapsed = ((double) (end - start));

    printf("Time ellapsed in openMP code is: %f seconds \n", time_ellapsed);
    return 0;
}