#include "Population.h"
#include "RandomGen.h"
#include <iostream>


Population::Population(int size, int length, int maxGen,
double elitism, double crossChance,
double mutationChance, double min, double max){
  this->elitism = elitism;
  this->crossChance = crossChance;
  this->mutationChance = mutationChance;
  this->min = min;
  this->max = max;
  this->maxGen = maxGen;
  this->currentGen = 0;
  this->chromosomes.reserve(size);
  this->fitnesses.reserve(size);
  this->relativeFitness.reserve(size);
  double sum = 0.0;
  for(int i = 0; i < size; i++){
    this->chromosomes.push_back(new Chromosome(length, min, max));
    this->fitnesses.push_back(this->chromosomes[i]->getFitness());
    sum += this->fitnesses[i];
  }
  double maximum = -1.0;
  for(int i = 0; i < size; i++){
    this->relativeFitness.push_back(this->fitnesses[i] / sum);
    if(this->fitnesses[i] > maximum){
      maximum = this->fitnesses[i];
      this->best = this->chromosomes[i];
    }
  }
}

Chromosome *Population::getBest(){
  return this->best;
}

void Population::calculateFitnesses(){
  double sum = 0.0;
  for(int i = 0; i < this->chromosomes.size(); i++){
    this->fitnesses[i] = this->chromosomes[i]->getFitness();
    sum += this->fitnesses[i] / sum;
  }
  double max = -1;
  int chromosome = 0;
  for(int i = 0; i < this->chromosomes.size(); i++){
    this->relativeFitness[i] = this->fitnesses[i] / sum;
    if(this->fitnesses[i] > max){
      max = this->fitnesses[i];
      chromosome = i;
    }
  }
  this->best = this->chromosomes[chromosome];
}

void Population::printStats(){
  double avg = 0.0;
  for(int i = 0; i < this->chromosomes.size(); i++){
    avg += this->fitnesses[i];
  }
  avg /= this->chromosomes.size();
  std::cout << "Generation #" << this->currentGen << " - Average fitness: "
  << avg << std::endl;
}

Population::~Population(){
  for(int i = 0; i < this->chromosomes.size(); i++){
    delete this->chromosomes[i];
  }
}

void Population::cross(){
  RandomGen r;
  for(int i = 0; i < this->chromosomes.size() - 1; i++){
    if(r.randomDouble() < this->crossChance){
      int n = this->chromosomes[0]->getSize();
      int point = r.randomInt(1, n - 1);
      for(int j = 0; j < point; j++){
        double temp = this->chromosomes[i]->getGene(j);
        this->chromosomes[i]->setGene(j, this->chromosomes[i + 1]->getGene(j));
        this->chromosomes[i + 1]->setGene(j, temp);
      }
    }
  }
}

Chromosome *Population::pickChromosome(){
  RandomGen r;
  double sum = 0.0, random = r.randomDouble();
  for(int i = 0; i < this->chromosomes.size(); i++){
    sum += this->relativeFitness[i];
    if(random < sum){
      return this->chromosomes[i];
    }
  }
  // So the compiler won't complain :/
  return this->chromosomes[0];
}

void Population::mutate(){
  RandomGen r;
  for(int i = 0; i < this->chromosomes.size(); i++){
    if(r.randomDouble() < this->mutationChance){
      for(int j = 0; j < this->chromosomes[i]->getSize(); j++){
        if(r.randomDouble() < this->mutationChance){
          double newGene = (this->max - this->min) * r.randomDouble() + this->min;
          this->chromosomes[i]->setGene(j, newGene);
        }
      }
    }
  }
}

bool Population::nextGen(){
  if(this->currentGen < this->maxGen){
    std::vector<Chromosome *> nextGeneration;
    int elite = (int)(this->chromosomes.size() * this->elitism);
    double max, prevMax = this->best->getFitness();
    nextGeneration.push_back(new Chromosome(best));
    for(int j = 1; j < elite; j++){
      max = -1;
      int bestCurrent;
      for(int i = 0; i < this->fitnesses.size(); i++){
        double current = this->fitnesses[i];
        if(current > max && current < prevMax){
          max = current;
          bestCurrent = i;
        }
      }
      nextGeneration.push_back(new Chromosome(this->chromosomes[bestCurrent]));
    }
    for(int i = elite; i < this->chromosomes.size(); i++){
      nextGeneration.push_back(new Chromosome(this->pickChromosome()));
    }
    for(int i = 0; i < this->chromosomes.size(); i++){
      delete this->chromosomes[i];
      this->chromosomes[i] = nextGeneration[i];
    }
    this->cross();
    this->mutate();
    this->currentGen++;
    this->calculateFitnesses();
    return true;
  }else{
    return false;
  }
}
