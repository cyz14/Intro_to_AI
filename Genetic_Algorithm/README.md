# Genetic Algorithm for TSP problem

## 说明( Statements )

### 编译( Compile )
#### 编程语言：C/C++
#### 编译环境：g++
#### 头文件( Head files )
|---lib(子目录)
  * Answer.h
  * city.h
  * Genetic.h
  * SimulatedAnnealing.h
  * TourMan.h


  在 src 目录下运行

    make Genetic
  即可

  或者在 src 目录下运行

    g++ Answer.cpp city.cpp Genetic.cpp SimulatedAnnealing.cpp main.cpp TourMan.cpp -o ../bin/homework4.exe

### 个体的编码方案
  整数的排列编码

### 交配方法( Crossove method )--常规交叉法
  随机选取一个交叉位，子代1交叉位之前的基因选自父代1交叉位之间的基因，交叉位之后的基因，从父代2中按顺序选取那些没有出现过的基因。

### 变异方法( Mutate method )--打乱变异
  随机产生两个位置 u 和 v，如果前者小于后者，则打乱这一段里的顺序。如果后者小于前者，则只交互两者。

### 新种群构成的方法( Next Generation )
  首先保留上一代中的最优个体。之后按照求出的适应值，用“轮盘赌”方法选出其他个体。在新一代中，数组中每两个连续的个体以杂交概率 pc 进行杂交，之后每个新个体以变异概率 pm 进行变异。

### 算法结束的条件
  遗传代数大于规定值。目前选取的是 1000*城市数量。
