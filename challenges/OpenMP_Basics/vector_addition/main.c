#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]){

  const int N = 1e7; // Size of vectors
  double A[N], B[N], C[N];
  double sum;
  double start, stop;

  // Initialize vectors A, B, C
  for(int i=0; i<N; i++){
    A[i] = sin(i)*sin(i);
    B[i] = cos(i)*cos(i);
    C[i] = 0.0;
  }

  start = omp_get_wtime();

  // Add elements of vectors A and B and accumulate in C
  #pragma omp parallel for default(none) shared(A, B, C)
  for(int i=0; i<N; i++){
    C[i] = A[i] + B[i];
  }

  stop = omp_get_wtime();

  // Sum all values of vector C
  for(int i=0; i<N; i++){
    sum = sum + C[i];
  }

  // Print results:
  // should be 1.00 because sin(x)*sin(x) + cos(x)*cos(x) = 1
  printf("The result is %.02f\n", sum/(1.0*N));
  printf("Time: %.06f\n", stop - start);

  return 0;
}
