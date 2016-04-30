# program for TourMan problem

all: Genetic.exe

CPP = Answer.cpp city.cpp Genetic.cpp SimulatedAnnealing.cpp main.cpp TourMan.cpp
HEAD = Answer.h city.h Genetic.h SimulatedAnnealing.h TourMan.h

Genetic.exe: $(CPP)
	g++ $(CPP) -o Genetic.exe -g

Test: $(CPP)
	g++ $(CPP) -o Genetic.exe -g -D_TEST_

clean:
	del *.exe
