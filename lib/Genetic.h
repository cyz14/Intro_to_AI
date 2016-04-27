#ifndef GENETIC_H
#define GENETIC_H

#include "../Answer.h"

extern const int SIZE;
extern const double pc; // probability of performing crossover
extern const double pm; // probability of mutation

class Genetic {
public:
  Genetic(std::vector<City> & , Answer * );
  ~Genetic();

  void workout(std::ostream &);
  void initPopulation(Answer *, int psize = SIZE);
  double fitvalue(const Answer &);
  int wheelSelection(double * prob, int size = SIZE);
private:
  Answer m_ans;
  const int ncity;
  std::vector<City> & m_vc;
};

#endif
