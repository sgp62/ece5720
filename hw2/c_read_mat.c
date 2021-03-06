/* from matlab use                                                    *
 *  save('MyMatrix.txt', 'A', '-ascii', '-double', '-tabs')           *
 *  and then use the code below to input the matrix from MyMatrix.txt */

#include<stdio.h>
#include<stdlib.h>

void printData(int N, int M, float** T){
  if (N <= 16){
    for (int x=0; x<N; x++){
      printf("| ");
      for(int y=0; y<M; y++)
        printf("% 5.2e ", T[x][y]);
      printf("|\n");
      }
    }
  else{
    printf("\nMatrix and vector too large to print out.\n");
  }
}

void data_A_b(int N, float** A, float** b, float** x){
  int i, j;
  int nrhs = 1;
  for (i=0; i<N; i++){
    for (j=0; j<N; j++)
      A[i][j] = (i+j) % 3;

    A[i][i] = A[i][i] + 1.0;
  }
  printf("A\n");
  printData(N, N, A);

  // for(int i = 0; i < N; i++){
  //   for(int k = 0; k < N; k++){
  //     b[i][k] = (i == k)? 1.0 : 0.0;
  //   }
  // }

  for(int i = 0; i < N; i++){
    for(int k = 0; k < N; k++){
      b[i][0] +=A[i][k];
    }
  }
  printf("b\n");
  printData(N, N, b);



  for(i = 0; i<N; i++) {
    int piv_indx = i;
    for(int j = i; j < N; j++){
      piv_indx = (abs(A[j][i]) > abs(A[piv_indx][i])) ? j : piv_indx;
    }
    /* your code for swapping rows i and piv_indx in A and b */
    for(int k = 0; k < N; k++){
      float temp = A[i][k];
      A[i][k] = A[piv_indx][k];
      A[piv_indx][k] = temp;
      if(nrhs != 1){
        float temp2 = b[i][k];
        b[i][k] = b[piv_indx][k];
        b[piv_indx][k] = temp2;
      }
      else if(k == 0){
        float temp2 = b[i][k];
        b[i][k] = b[piv_indx][k];
        b[piv_indx][k] = temp2;
      }
    }

    for(int j = i+1; j < N; j++){
      float p = A[j][i] / A[i][i];
      for(int k = 0; k < N; k++){
        A[j][k] = A[j][k] - p * A[i][k];
        if(nrhs != 1){
          b[j][k] = b[j][k] - p * b[i][k];
        }
        else if(k==0) b[j][k] = b[j][k] - p * b[i][k];
      }
    }
  }
  printf("A\n");
  printData(N, N, A);
  printf("b\n");
  printData(N, N, b);

  for(int i= N-1 ;i >= 0; i--){  // loop over # rhs
    if(nrhs == 1){
      x[i][0] = b[i][0]/A[i][i];
      for(int j = i-1; j >= 0; j--){
        b[j][0] = b[j][0] - A[j][i] * x[i][0];
        //A[j][i] = A[j][i] - A[j][i] * x[i][0];
      }
    }
    else{ // Matrix inversion method
      for(int m = N-1; m >= 0; m--){
        float temp = b[m][i]/A[m][m];
        for(int j = i-1; j >= 0; j--){
          b[m][j] = b[m][j] - A[j][m] * b[m][i];
        }
      }
    }
  }

  // for(int i = N-1; i > 0; i--){
  //   float temp = A[j][j];
  //   for(int i = 0; i < N; i++){
  //     A[j][i] = A[j][i] / temp;
  //     b[j][i] = b[j][i] / temp;
  //   }
  // }

  printf("A\n");
  printData(N, N, A);
  printf("b\n");
  printData(N, N, b);
  printf("x\n");
  printData(N, N, x);

  
  // for(i = 0; i<N; i++) {
  //   int piv_indx = i; 
  //   for(int j = i; j < N; j++){
  //     piv_indx = (A[j][i] > A[piv_indx][i]) ? j : piv_indx;
  //   }
  //     /* your code for swapping rows i and piv_indx in A and b */
  // }




/* create b, either as columns of the identity matrix, or */
/* when Nrhs = 1, assume x all 1s and set b = A*x         */

  // for(int i = 0; i < N; i++){
  //   for(int k = 0; k < N; k++){
  //     b[i][0] += A[i][k];
  //   }
  // }



  //printf("here\n");
  //fflush(stdout);

}


// thread myid finds index piv_indx of pivot row in column i
// and next swaps rows i and  piv_indx 


int main()
{
  int i,j,N;
  N = 4;

  float **A = (float **)malloc(N*sizeof(float*));
    for (int q=0; q < N; q++)
      A[q] = (float*)malloc(N*sizeof(float));

  float** b = (float**) malloc(N*sizeof(float*));
    for (int q=0; q < N; q++)
      b[q] = (float*)malloc(N*sizeof(float));

  float** x = (float**) malloc(N*sizeof(float*));
    for (int q=0; q < N; q++)
      x[q] = (float*)malloc(N*sizeof(float));



  data_A_b(N,A,b,x);
  //printData(N,N,b);
  free(A);
  free(b);
}


