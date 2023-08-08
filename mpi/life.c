#include "life.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void life(int argc, char *argv[], bool **output, const long unsigned int g,
          const long unsigned int n, const bool **input) {
  bool **even = (bool **)malloc(n * sizeof(bool *));
  bool **odd = (bool **)malloc(n * sizeof(bool *));
  for (long unsigned int i = 0; i < n; ++i) {
    even[i] = (bool *)malloc(n * sizeof(bool));
    odd[i] = (bool *)malloc(n * sizeof(bool));
  }
  const bool ***present;
  bool ***future;
  present = &input;

  for (long unsigned int generation = 0; generation < g; ++generation) {
    future = generation & 1 ? &odd : &even;
    for (long unsigned int i = 0; i < n; ++i) {
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
  }
  for (long unsigned int i = 0; i < n; ++i) {
    for (long unsigned int j = 0; j < n; ++j) {
      output[i][j] = (*present)[i][j];
    }
  }

  // Libera memória
  for (long unsigned int i = 0; i < n; ++i) {
    free(even[i]);
    free(odd[i]);
  }
  free(even);
  free(odd);
}
