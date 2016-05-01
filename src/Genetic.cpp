
#include "../lib/Genetic.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
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

extern const int SIZE = 20;     // colony population size
extern const double pc = 1.0;   // probability of crossover
extern const double pm = 0.05;  // probability of mutation
const double INF = 1e32;

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

  int t = 0;
  double bestAnswer = 0.0;
  int bestGeneId = -1;

  initPopulation(colony, SIZE);

  int gene_num = 1000 * ncity;
  while (t < gene_num) { // 结束条件： 遗传代数到达城市数目的1000倍

    bestGeneId = nextGeneration(colony, nextGene);
    bestAnswer = total_cost(*colony[bestGeneId]);
    // print(fout, colony[bestGeneId]);

    // (9)
    for (size_t i = 0; i < SIZE; i++) {
      *colony[i] = *nextGene[i];
    }
    t = t + 1;
  }
  // (10)
  print(fout, colony[bestGeneId]);
  std::cout << bestAnswer << std::endl;
}

void Genetic::crossover(Answer * fa, Answer * mo) {
  normal_cross(fa, mo); // 常规交叉法
}

void Genetic::normal_cross(Answer * fa, Answer * mo) { // 常规交叉法
  int pos = rand() % ncity;
  // std::cout << "pos: " << pos << std::endl;
  Answer so1(*fa);
  Answer so2(*mo);
  double rev = Answer::rand_0_1();
  if (rev < 0.8) {
    fa->reverse();
    mo->reverse();
  }

  int * fa_occur = new int[ncity];
  int * mo_occur = new int[ncity];
  for (size_t i = 0; i < ncity; i++) {
    fa_occur[i] = mo_occur[i] = 0;
  }

  for (size_t i = 0; i < pos; i++) {
    // std::cout << (*fa)[i] << ' ' << (*mo)[i] << std::endl;
    so1.setAt(i, (*fa)[i]);
    so2.setAt(i, (*mo)[i]);
    // std::cout << so1[i] << ' ' << so2[i] << std::endl;
    fa_occur[ so1[i] ] = 1;
    mo_occur[ so2[i] ] = 1;
  }

  int mpos = pos;
  for (size_t i = 0; i < ncity && (pos < ncity || mpos < ncity); i++) {
    // when pos or mpos < ncity, loop should not stop
    if (!fa_occur[ (*mo)[i] ]) {
      so1.setAt(pos++, (*mo)[i]);
      fa_occur[ (*mo)[i] ] = 1;
    }

    if (!mo_occur[ (*fa)[i] ]) {
      so2.setAt(mpos++, (*fa)[i]);
      mo_occur[ (*fa)[i] ] = 1;
    }
  }

  delete [] fa_occur;
  delete [] mo_occur;
  *fa = so1;
  *mo = so2;
}

// has bug
void Genetic::pair_cross(Answer * fa, Answer * mo) { // 部分映射的交叉法
  int * a = new int[ncity];
  int * b = new int[ncity];
  int u = 0, v = 0;
  fa->randomUV(u, v, 0, 0);
  if (u > v)
    std::swap(u, v);

  for (size_t i = 0; i < ncity; i++) {
    a[i] = b[i] = -1;
  }

  std::cout << u << ' ' << v << std::endl;
  for (size_t i = 0; i < ncity; i++) {
    if (i < u || i > v) {
      if (a[ (*fa)[i] ] == -1)
        a[ (*fa)[i] ] = (*fa)[i];
      if (b[ (*mo)[i] ] == -1)
        b[ (*mo)[i] ] = (*mo)[i];
    }
    else {
      a[ (*fa)[i] ] = (*mo)[i];
      a[ (*mo)[i] ] = (*fa)[i];
      b[ (*mo)[i] ] = (*fa)[i];
      b[ (*fa)[i] ] = (*mo)[i];
    }
  }

  for (size_t i = 0; i < ncity; i++) {
    int ta = a[ (*fa)[i] ];
    int tb = b[ (*mo)[i] ];
    fa->setAt(i, ta);
    mo->setAt(i, tb);
  }
}

void Genetic::mutate(Answer * so) { // 打乱变异
  int u = 0, v = 0;
  so->randomUV(u, v, 0, 0);
  so->random(u ,v);
}

void Genetic::initPopulation(Answer ** colony, int psize) {
  for (size_t i = 0; i < psize; ++i) {
    colony[i]->random();
  }
}

int Genetic::nextGeneration(Answer ** colony, Answer ** nextGene) {
  double * fit = new double[SIZE];
  double sumFit = 0.0;
  double bestFitVal = 0.0;
  int bestGeneId = 0;

  // calculate fit values
  for (size_t i = 0; i < SIZE; ++i) {
    fit[i] = fitvalue(*colony[i]);
    sumFit += fit[i];

    if (fit[i] > bestFitVal) {
      bestFitVal = fit[i];
      bestGeneId = i;
    }
  }

  double * prob = new double[SIZE];
  for (size_t i = 0; i < SIZE; i++) {
    prob[i] = fit[i] / sumFit;
  }

  *nextGene[0] = *colony[bestGeneId]; // best chromosome should be kept
  for (size_t i = 1; i < SIZE; i++) {
    int id = wheelSelection(prob, SIZE);
    // std::cout << id << std::endl;
    (*nextGene[i]) = (*colony[id]);
  }

  // (7) Crossover
  for (size_t i = 1, j = 2; j < SIZE; i += 2, j += 2) {
    double p = Answer::rand_0_1();
    if (p < pc) {
      crossover(nextGene[i], nextGene[j]);
    }
  }
  // (8) Mutate
  for (size_t i = 1; i < SIZE; i++) {
    double p = Answer::rand_0_1();
    if (p < pm) {
      mutate(nextGene[i]);
    }
  }
  return bestGeneId;
}


double Genetic::total_cost(const Answer & answer) {
  double dist = 0.0;
  for (int i = 0, j = 1; i < ncity; ++i, ++j)
  {
    if (j == ncity) j = 0;
    dist += m_vc[ answer[i] ].distanceTo(m_vc[ answer[j] ]);
  }
  return dist;
}

double Genetic::fitvalue(const Answer & answer) {
  double dist = total_cost(answer);
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

void Genetic::print(std::ostream & fout, Answer * answer) {
  for (size_t i = 0; i < ncity; i++) {
    fout << m_vc[(*answer)[i]].getName() << ' ';
    if (i + 1 == ncity) {
      fout << std::setprecision(5) << total_cost(*answer) << std::endl;
    }
  }
}

void Genetic::test_crossover() {
  Answer ** colony = new Answer*[SIZE];
  for (size_t i = 0; i < SIZE; i++) {
    colony[i] = new Answer(ncity);
  }
  initPopulation(colony, SIZE);

  for (size_t i = 0, j = 1; j < SIZE; i+=2, j+=2) {
    std::cout << "##### Crossover " << i << " #####" << std::endl;
    std::cout << "##### Before " << " #####" << std::endl;
    std::cout << fitvalue(*colony[i]) << ' ';
    colony[i]->print();
    std::cout << fitvalue(*colony[i]) << ' ';
    colony[j]->print();

    crossover(colony[i], colony[j]);

    std::cout << "##### After " << " #####" << std::endl;
    std::cout << fitvalue(*colony[i]) << ' ';
    colony[i]->print();
    std::cout << fitvalue(*colony[i]) << ' ';
    colony[j]->print();
  }

  for (size_t i = 0; i < SIZE; i++) {
    delete colony[i];
  }
  delete [] colony;
}

void Genetic::test_mutate() {
  Answer ** colony = new Answer*[SIZE];
  for (size_t i = 0; i < SIZE; i++) {
    colony[i] = new Answer(ncity);
  }
  initPopulation(colony, SIZE);
  std::cout << std::setprecision(4) << std::endl;
  for (size_t i = 0; i < SIZE; i++) {
    std::cout << "##### Mutate" << i << " #####" << std::endl;
    std::cout << fitvalue(*colony[i]) << ' ';
    colony[i]->print();

    mutate(colony[i]);

    std::cout << fitvalue(*colony[i]) << ' ';
    colony[i]->print();
    std::cout << "##### Mutate" << i << " #####" << std::endl;
  }
  for (size_t i = 0; i < SIZE; i++) {
    delete colony[i];
  }
  delete [] colony;
}

void Genetic::test() {
  test_crossover();
  // test_mutate();
  Answer ** colony = new Answer*[SIZE];
  for (int i = 0; i < SIZE; ++i)
  {
    colony[i] = new Answer(ncity);
  }

  double * fitv = new double[SIZE];
  double sumFit = 0.0;
  for (int i = 0; i < SIZE; ++i)
  {
    fitv[i] = fitvalue(*colony[i]);
    sumFit += fitv[i];
  }
  double * prob = new double[SIZE];
  for (int i = 0; i < SIZE; ++i)
  {
    prob[i] = fitv[i] / sumFit;
  }
  for (int i = 0; i < SIZE; ++i)
  {
    std::cout << wheelSelection(prob, SIZE) << std::endl;
  }

  for (size_t i = 0; i < SIZE; i++) {
    delete colony[i];
  }
  delete [] colony;
}
