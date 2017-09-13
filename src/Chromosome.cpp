#include "Chromosome.h"
#include "RandomGen.h"
#include <iostream>
#include <cmath>

Chromosome::Chromosome(int size, double min, double max){
  this->genes.reserve(size);
  RandomGen r;
  double num;
  for(int i = 0; i < size; i++){
    num = (max - min) * r.randomDouble() + min;
    this->genes.push_back(num);
  }
}

int Chromosome::getSize(){
  return this->genes.size();
}

void Chromosome::printChromosome(){
  for(int i = 0; i < this->getSize(); i++){
    std::cout << this->genes[i] << " ";
  }
  std::cout << "- Fitness: " << this->getFitness() << std::endl;
}

void Chromosome::setGene(int index, double value){
  if(index >= this->genes.size()){
    return;
  }
  this->genes[index] = value;
}

void Chromosome::copy(Chromosome *c){
  this->genes.clear();
  for(int i = 0; i < c->getSize(); i++){
    this->genes.push_back(c->getGene(i));
  }
}

double Chromosome::getGene(int index){
  return this->genes[index];
}

void Chromosome::swapGenes(int a, int b){
  if(a >= this->genes.size() || b >= this->genes.size()){
    return;
  }
  double temp = this->genes[a];
  this->genes[a] = this->genes[b];
  this->genes[b] = temp;
}

Chromosome::Chromosome(Chromosome *copy){
  this->genes.reserve(copy->getSize());
  for(int i = 0; i < copy->getSize(); i++){
    this->genes.push_back(copy->getGene(i));
  }
}

double Chromosome::getFitness(){
  double pi = 3.14159265359;
  double fitness = 0.0, sum = 0.0;
  fitness += 2 * this->getSize();
  for(int i = 0; i < this->getSize(); i++){
    sum += cos(5 * pi * this->genes[i]);
    fitness += pow(this->genes[i], 2);
  }
  sum *= 0.1;
  fitness -= sum;
  return fitness;
}
