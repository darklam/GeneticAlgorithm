#ifndef POPULATION_H
#define POPULATION_H
#include "Chromosome.h"

class Population{
private:
  std::vector<Chromosome *> chromosomes;
  double mutationChance, elitism, crossChance, min, max;
  std::vector<double> fitnesses, relativeFitness;
  Chromosome *best;
  int maxGen, currentGen;
  void cross();
  void mutate();
  void calculateFitnesses();
  Chromosome *pickChromosome();

public:
  Population(int, int, int, double, double, double, double, double);
  ~Population();
  bool nextGen();
  void printStats();
  Chromosome *getBest();
};
#endif
