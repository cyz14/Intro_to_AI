
#include "../lib/Genetic.h"
#include <iostream>
/*
遗传算法
（1）给定群体规模N，交叉概率pc和变异概率pm，t＝0；
（2）随机生成N个染色体作为初始群体；
（3）对于群体中的每一个染色体xi分别计算其适应值F(xi)；
（4）如果算法满足停止准则，则转（10）；
（5）对群体中的每一个染色体xi计算概率；
（6）依据计算得到的概率值，从群体中随机的选取N个染色体，得到种群；
（7）依据交叉概率pc从种群中选择染色体进行交叉，其子代进入新的群体，种群中未进行交叉的染色体，
    直接复制到新群体中；
（8）依据变异概率pm从新群体中选择染色体进行变异，用变异后的染色体代替新群体中的原染色体；
（9）用新群体代替旧群体，t=t+1，转（3）；
（10）进化过程中适应值最大的染色体，经解码后作为最优解输出；
（11）结束。

*/

/*
## Outline of the Basic Genetic Algorithm
// from obitko.com/tutorials/genetic-algorithms/ga-basic-description.php

1. [Start] Generate random population of n chromosomes (suitable solutions for the problem)
2. [Fitness] Evaluate the fitness f(x) of each chromosome x in the population
3. [New population] Create a new population by repeating following steps until the new population is complete
      1. [Selection] Select two parent chromosomes from a population according to their fitness (the better fitness, the bigger chance to be selected)
      2. [Crossover] With a crossover probability cross over the parents to form a new offspring (children). If no crossover was performed, offspring is an exact copy of parents.
      3. [Mutation] With a mutation probability mutate new offspring at each locus (position in chromosome).
      4. [Accepting] Place new offspring in a new population
4. [Replace] Use new generated population for a further run of algorithm
5. [Test] If the end condition is satisfied, stop, and return the best solution in current population
6. [Loop] Go to step 2


Making new population only by new offspring can cause lost of the best chromosome from the last population. This is true, so so called elitism is often used. This means, that at least one best solution is copied without changes to a new population, so the best solution found can survive to end of run.

*/

extern const int SIZE = 100;
extern const double pc = 1.00;
extern const double pm = 0.01;

Genetic::Genetic(std::vector<City> & vc, Answer * answer)
  : m_vc(vc), m_ans(answer), ncity(vc.size())
{
#ifdef _LOCAL_
  std::cout << "city number: " << ncity << std::endl;
#endif
}

Genetic::~Genetic() {}

void Genetic::workout(std::ostream & fout) {
  // Answer answer(ncity);

  Answer ** colony = new Answer*[SIZE];
  for (size_t i = 0; i < SIZE; i++) {
    colony[i] = new Answer(ncity);
  }
  Answer ** nextGene = new Answer*[SIZE];
  for (size_t i = 0; i < SIZE; i++) {
    nextGene[i] = new Answer(ncity);
  }

  double * fit = new double[SIZE];
  double * prob = new double[SIZE];

  int t = 0;
  initPopulation(colony, SIZE);

  int bestGeneId = 0;
  double bestFitVal = 0.0;
  double sumFit = 0.0;
  for (size_t i = 0; i < SIZE; ++i) {
    fit[i] = fitvalue(*colony[i]);
    sumFit += fit[i];

    if (fit[i] > bestFitVal) {
      bestFitVal = fit[i];
      bestGeneId = i;
    }
  }
  
  for (size_t i = 0; i < SIZE; i++) {
    prob[i] = fit[i] / sumFit;
  }

  for (size_t i = 0; i < SIZE; i++) {
    int id = wheelSelection(prob, SIZE);
    std::cout << id << std::endl;
    (*nextGene[i]) = (*colony[id]);
  }

  // (7)

  // (8)
  // (9)
  // (10)

}

void Genetic::initPopulation(Answer ** colony, int psize) {
  for (size_t i = 0; i < psize; ++i) {
    colony[i]->random();
  }
}

double Genetic::fitvalue(const Answer & answer) {
  double dist = 0.0;
  for (int i = 0, j = 1; i < ncity; ++i, ++j)
  {
    if (j == ncity) j = 0;
    dist += m_vc[ answer[i] ].distanceTo(m_vc[ answer[j] ]);
  }
  return 1.0 / dist;
}

int Genetic::wheelSelection(double * prob, int size) {
  double s = 0.0;
  int i = 0;
  double p = Answer::rand_0_1();
  for (size_t i = 0; i < size; i++) {
    if (s >= p) {
      return i;
    }
    s += prob[i];
  }
  return 0;
}
