#include "../lib/TourMan.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char * argv[]) {
  TourMan man;
  if (argc < 3) {
    cerr << "Error: no enough files specified." << endl;
    return -1;
  }

  ifstream fin;
  fin.open(argv[1]);
  if (!fin.is_open()) {
    cerr << "Error: failed to open input file." << endl;
    return -1;
  }

  ofstream fout;
  fout.open(argv[2]);
  if (!fout.is_open()) {
    cerr << "Error: failed to open output file." << endl;
    return -1;
  }

  srand((unsigned int)time(NULL));
  man.input(fin);
  man.workout(fout);
  // man.test();

  return 0;
}
