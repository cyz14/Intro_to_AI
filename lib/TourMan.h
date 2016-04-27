#ifndef TOURMAN_H
#define TOURMAN_H

#include "../lib/SimulatedAnnealing.h"

class TourMan {

public:
  TourMan();
  ~TourMan();

  void test();
  void input(std::istream &);
  void workout(std::ostream &);
  void printPath(std::ostream &);
  double cost(const Answer &);

private:
  int ncity;
  std::vector<City> vc;
  Answer * ans;
};

#endif
