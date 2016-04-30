#ifndef GENETIC_H
#define GENETIC_H

#include "./Answer.h"
#include "./city.h"

extern const int SIZE;
extern const double pc; // probability of performing crossover
extern const double pm; // probability of mutation

class Genetic {
public:
  Genetic(std::vector<City> & , Answer * );
  ~Genetic();

  void test();
  void workout(std::ostream &);
  void initPopulation(Answer **, int psize = SIZE);
  double fitvalue(const Answer &);
  double total_cost(const Answer &);
  int wheelSelection(double * prob, int size = SIZE);
  void crossover(Answer *, Answer *);
  void normal_cross(Answer *, Answer *);
  void pair_cross(Answer *, Answer *);
  void mutate(Answer *);

  void test_crossover_mutate();
private:
  Answer * m_ans;
  const int ncity;
  std::vector<City> & m_vc;
};

#endif
