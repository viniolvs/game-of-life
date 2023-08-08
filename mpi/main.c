#include "life.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
  struct timeval timevalA;
  struct timeval timevalB;
  long unsigned int n;
  scanf("%lu", &n);
  long unsigned int generations;
  int i, j;
  int temp;

  // Aloca memória para a matriz de entrada
  bool **input = (bool **)malloc(n * sizeof(bool *));
  for (i = 0; i < n; i++) {
    input[i] = (bool *)malloc(n * sizeof(bool));
    for (j = 0; j < n; j++) {
      scanf("%d", &temp);
      input[i][j] = temp;
    }
  }

  // Aloca memória para a matriz de saída
  bool **output = (bool **)malloc(n * sizeof(bool *));
  for (i = 0; i < n; i++) {
    output[i] = (bool *)malloc(n * sizeof(bool));
    for (j = 0; j < n; j++) {
      output[i][j] = 0;
    }
  }

  scanf("%lu", &generations);

  // Restante do código...
  // (Lógica do Game of Life, processamento MPI, etc.)
  // grava o tempo de execução
  gettimeofday(&timevalA, NULL);
  life(argc, argv, output, (const long unsigned int)generations,
       (const long unsigned int)n, (const bool **)input);
  gettimeofday(&timevalB, NULL);
  double timeDifference =
      timevalB.tv_sec - timevalA.tv_sec +
      (timevalB.tv_usec - timevalA.tv_usec) / (double)1000000;

  printf("%.6lf\n", timeDifference);
  //
  // printa matriz de saída
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%d ", output[i][j]);
    }
    printf("\n");
  }
  // Libera memória da matriz de entrada
  for (i = 0; i < n; i++) {
    free(input[i]);
  }
  free(input);

  // Libera memória da matriz de saída
  for (i = 0; i < n; i++) {
    free(output[i]);
  }
  free(output);

  return EXIT_SUCCESS;
}
