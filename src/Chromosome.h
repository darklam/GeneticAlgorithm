#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <vector>

class Chromosome{
private:
  // The genes of the chromosome duuh
  std::vector<double> genes;

public:
  // Returns the genes vector
  std::vector<double> getGenes();
  // Returns the size of the gene array
  int getSize();
  // The constructor arguments are the size of the chromosome
  // the min and the max gene values
  Chromosome(int, double, double);
  // Initialize the object from another chromosome
  Chromosome(Chromosome *);
  // Returns the fitness of the chromosome
  double getFitness();
  // Sets the gene at index to the specified value
  void setGene(int, double);
  // Swaps the genes at indexes
  void swapGenes(int, int);
  // Returns the gene at index
  double getGene(int);
  // Prints the chromosome to the screen
  void printChromosome();
  // Copy from another chromosome
  void copy(Chromosome *);
};
#endif
