/**Matrix multiplication using sequential code*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
     
#define a 100
#define b 100
#define c 100

int main() 
{
    int A[a][b] = {0} ;
    int B[b][c] = {0}  ;
    int C[a][c]={0};
    srand(time(NULL));

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
    for (int i = 0; i < a; ++i) { //for every row of A
        for (int j = 0; j < c; ++j) { //for every column of B
            for (int k = 0; k < b; ++k) { //for k (0-> shared dimension)
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = clock();
    time_ellapsed = ((double) (end - start)/ CLOCKS_PER_SEC);

    printf("Time ellapsed in sequential code is: %f seconds\n", time_ellapsed);
    return 0;
}