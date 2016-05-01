# program for TourMan problem

all: Genetic

CPP = Answer.cpp city.cpp Genetic.cpp SimulatedAnnealing.cpp main.cpp TourMan.cpp
HEAD = Answer.h city.h Genetic.h SimulatedAnnealing.h TourMan.h

Genetic: $(CPP)
	g++ $(CPP) -o ../bin/homework4.exe -g

Test: $(CPP)
	g++ $(CPP) -o ../bin/homework4.exe -g -D_TEST_

clean:
	del *.exe *.txt
