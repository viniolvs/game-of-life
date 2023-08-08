#include "life.h"
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void life(int argc, char *argv[], bool **output, const long unsigned int g,
          const long unsigned int n, const bool **input) {

  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // Divide a entrada em partes iguais e envia para os processos escravos
  int PART_SIZE = n / size;
  // se o processo for 0, ele é o mestre
  if (rank == 0) {
    for (int i = 1; i < size; i++) {
      MPI_Send(&input[i * PART_SIZE][0], PART_SIZE * n, MPI_C_BOOL, i, 0,
               MPI_COMM_WORLD);
    }
  }
  // se o processo for diferente de 0, ele é escravo
  else {
    input = (const bool **)malloc(PART_SIZE * sizeof(bool *));
    for (long unsigned int i = 0; i < PART_SIZE; ++i) {
      input[i] = (bool *)malloc(n * sizeof(bool));
    }
    MPI_Recv(&input[0][0], PART_SIZE * n, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }

  bool **even = (bool **)malloc(PART_SIZE * sizeof(bool *));
  bool **odd = (bool **)malloc(PART_SIZE * sizeof(bool *));
  for (long unsigned int i = 0; i < n; ++i) {
    even[i] = (bool *)malloc(n * sizeof(bool));
    odd[i] = (bool *)malloc(n * sizeof(bool));
  }
  const bool ***present;
  bool ***future;
  present = &input;

  for (long unsigned int generation = 0; generation < g; ++generation) {
    future = generation & 1 ? &odd : &even;
    for (long unsigned int i = 0; i < PART_SIZE; ++i) {
      for (long unsigned int j = 0; j < n; ++j) {
        long unsigned int neighbors = 0;
        if (i > 0) {
          if (j > 0) {
            if ((*present)[i - 1][j - 1]) {
              ++neighbors;
            }
          }
          if ((*present)[i - 1][j]) {
            ++neighbors;
          }
          if (j < n - 1) {
            if ((*present)[i - 1][j + 1]) {
              ++neighbors;
            }
          }
        }
        if (j > 0) {
          if ((*present)[i][j - 1]) {
            ++neighbors;
          }
        }
        if (j < n - 1) {
          if ((*present)[i][j + 1]) {
            ++neighbors;
          }
        }
        if (i < n - 1) {
          if (j > 0) {
            if ((*present)[i + 1][j - 1]) {
              ++neighbors;
            }
          }
          if ((*present)[i + 1][j]) {
            ++neighbors;
          }
          if (j < n - 1) {
            if ((*present)[i + 1][j + 1]) {
              ++neighbors;
            }
          }
        }
        (*future)[i][j] = neighbors == 3 || (*present)[i][j] && neighbors == 2;
      }
    }
    present = (const bool ***)future;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allgather(&(*present)[0][0], PART_SIZE * n, MPI_C_BOOL, &input[0][0],
                  PART_SIZE * n, MPI_C_BOOL, MPI_COMM_WORLD);
  }
  for (long unsigned int i = 0; i < n; ++i) {
    for (long unsigned int j = 0; j < n; ++j) {
      output[i][j] = (*present)[i][j];
    }
  }

  // Libera memória
  for (long unsigned int i = 0; i < PART_SIZE; ++i) {
    free(even[i]);
    free(odd[i]);
  }
  free(even);
  free(odd);
  MPI_Finalize();
}
