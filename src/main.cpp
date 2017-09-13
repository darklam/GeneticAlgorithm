#include "Population.h"
#include "Chromosome.h"
#include <iostream>


int main(){
  double min = -1.0, max = 1.0, mutation = 0.1, cross = 0.2, elitism = 0.1;
  int length = 5, populationSize = 10000, maxGen = 1000;
  Population lol(
    populationSize, length, maxGen, elitism, cross, mutation, min, max);
  Chromosome *best = new Chromosome(5, -1, 1);
  while(lol.nextGen()){
    if(lol.getBest()->getFitness() > best->getFitness()){
      best->copy(lol.getBest());
    }
    lol.printStats();
  }
  best->printChromosome();
  return 0;
}
