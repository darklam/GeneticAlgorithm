#include "RandomGen.h"
#include <random>

double RandomGen::randomDouble(){
  double min = 0, max = 1;
  std::uniform_real_distribution<double> dist(min, max);
  std::random_device rd;
  std::mt19937 re(rd());
  return dist(re);
}

int RandomGen::randomInt(int min, int max){
  std::random_device rd;
  std::mt19937 re(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(re);
}
