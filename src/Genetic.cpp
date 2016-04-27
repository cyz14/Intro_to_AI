
#include "../lib/Genetic.h"

/*
遗传算法
（1）给定群体规模N，交叉概率pc和变异概率pm，t＝0；
（2）随机生成N个染色体作为初始群体；
（3）对于群体中的每一个染色体xi分别计算其适应值F(xi)；
（4）如果算法满足停止准则，则转（10）；
（5）对群体中的每一个染色体xi计算概率；
（6）依据计算得到的概率值，从群体中随机的选取N个染色体，得到种群；
（7）依据交叉概率pc从种群中选择染色体进行交叉，其子代进入新的群体，种群中未进行交叉的染色体，直接复制到新群体中；
（8）依据变异概率pm从新群体中选择染色体进行变异，用变异后的染色体代替新群体中的原染色体；
（9）用新群体代替旧群体，t=t+1，转（3）；
（10）进化过程中适应值最大的染色体，经解码后作为最优解输出；
（11）结束。

*/

extern const int SIZE = 100;
extern const double pc = 1.00;
extern const double pm = 0.01;

Genetic::Genetic(std::vector<City> & vc, Answer * answer)
  : m_vc(vc), m_ans(answer), ncity(vc.size())
{}

Genetic::~Genetic() {}

void Genetic::workout(std::ostream & fout) {
  // Answer answer(ncity);

  Answer * colony = new Answer[SIZE];
  Answer * nextGene = new Answer[SIZE];
  double * fit = new double[SIZE];
  double * prob = new double[SIZE];

  int t = 0;
  initPopulation(colony, SIZE);

  double sumFit = 0.0;
  for (size_t i = 0; i < SIZE; ++i) {
    fit[i] = fitvalue(colony[i]);
    sumFit += fit[i];
  }
  for (size_t i = 0; i < SIZE; i++) {
    prob[i] = fit[i] / sumFit;
  }

  for (size_t i = 0; i < SIZE; i++) {
    int id = wheelSelection(prob, SIZE);
    nextGene[i] = colony[id];
  }

  // (7)
  // (8)
  // (9)
  // (10)

}

void Genetic::initPopulation(Answer * colony, int psize) {
  for (size_t i = 0; i < psize; ++i) {
    colony[i].random();
  }
}

double Genetic::fitvalue(const Answer & answer) {
  double dist = 0.0;
  for (int i = 0, j = 1; i < ncity; ++i, ++j)
  {
    if (j == ncity) j = 0;
    dist += m_vc[ ans[i] ].distanceTo(m_vc[ ans[j] ]);
  }
  return 1.0 / dist;
}

int Genetic::wheelSelection(double * prob, int size) {
  double s = 0.0;
  int i = 0;
  double p = answer.rand_0_1();
  for (size_t i = 0; i < size; i++) {
    if (s >= p) {
      return i;
    }
    s += prob[i];
  }
  return 0;
}
