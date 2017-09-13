HFILES=Chromosome.h Population.h RandomGen.h
CPPFILES=$(HFILES:.h=.cpp) main.cpp
OBJFILES=$(CPPFILES:.cpp=.o)
CXX=g++
FLAGS=-std=c++11 -Wall -Ofast

all: $(OBJFILES)
	$(CXX) $(OBJFILES) $(FLAGS) -o prog

%.o: %.cpp
	$(CXX) -c $(FLAGS) $< -o $@

clean:
	rm *.o
