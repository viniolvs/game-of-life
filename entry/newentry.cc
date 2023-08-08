#include <iostream>

using namespace std;

int main(int argc, char *argv[]) try {
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " <matrix_size> <generations>" << endl;
    return EXIT_FAILURE;
  }
  long unsigned int n = stoul(argv[1]);
  long unsigned int generations = stoul(argv[2]);
  // generate input
  cout << n << endl;
  for (long unsigned int i = 0; i < n; ++i) {
    for (long unsigned int j = 0; j < n; ++j) {
      // gen random 0 or 1
      cout << rand() % 2;
      if (j < n - 1) {
        cout << " ";
      }
    }
    cout << endl;
  }
  cout << generations << endl;
  return EXIT_SUCCESS;
} catch (...) {
  cerr << "EXIT_FAILURE";
  return EXIT_FAILURE;
}
