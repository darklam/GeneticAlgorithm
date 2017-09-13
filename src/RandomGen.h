#ifndef RANDOMGEN_H
#define RANDOMGEN_H

class RandomGen{  //A class for generating random values
public:
  //Returns a random double in the range 0 (inclusive) to 1 (inclusive)
  double randomDouble();
  //Returns a random int in the range min (inclusive) to max (inclusive)
  int randomInt(int, int);

};

#endif
