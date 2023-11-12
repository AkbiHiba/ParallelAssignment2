/**Matrix multiplication sing p threads*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<pthread.h>

void *matrix_multiply(void *arg);
     
#define a 500
#define b 500
#define c 500
#define num_threads 1
int A[a][b] = {0} ;
int B[b][c] = {0}  ;
int C[a][c]={0};


int main() {

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

    
    clock_t start, end;
    double time_ellapsed;
    start = clock();
    //create array of threads
    pthread_t * threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t));
    //intilaize and create each thread, pass the tid to the thread
    for ( int i = 0; i < num_threads; ++i ) {
        int *tid;
        tid = (int *) malloc( sizeof(int) );
        *tid = i;
        pthread_create( &threads[i], NULL, matrix_multiply, (void *)tid );
    }
    //join the threads once finished
    for ( int i = 0; i < num_threads; ++i ) {
        pthread_join( threads[i], NULL);
    }

    end = clock();
    time_ellapsed = ((double) (end - start)/ CLOCKS_PER_SEC);

    printf("Time ellapsed in p-thread code is: %f seconds\n", time_ellapsed);
    return 0;
}

void *matrix_multiply(void *arg) {
    //retirve the tid of the curren thread
    int tid = *(int *)arg;
    //assign to the thread a region
    int region_size = a/num_threads;
    int row_start = tid * region_size;
    int row_end = (tid+1) * region_size;

    int i,j;
    for (i = row_start; i < row_end; ++i) { //for every row of A
        for (j = 0; j < c; ++j) { //for every column of B
            for (int k = 0; k < b; ++k) { //for k (0-> shared dimension)
                C[i][j] += A[i][k] * B[k][j];
            }
        }
   }

   pthread_exit(0);
}