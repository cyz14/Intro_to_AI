

#include "../lib/Answer.h"
#include "../lib/TourMan.h"
#include "../lib/SimulatedAnnealing.h"
#include "../lib/Genetic.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cmath>

// implementation must be away with definitions
TourMan::TourMan() : ncity(0) {}

TourMan::~TourMan() {}

void TourMan::test() {
}

void TourMan::input(std::istream & fin) {
	fin >> ncity;
	assert(ncity > 0);

	ans = new Answer(ncity);
	for (int i = 0; i < ncity; i++)
	{
		float x, y;
		char name;
		fin >> name >> x >> y;
#ifdef _LOCAL_
		std::cout << name << ' ' << x << ' ' << y << std::endl;
#endif
		City tc(x, y, i, name);
		tc.setId(i);
		vc.push_back(tc);
	}
}

void TourMan::workout(std::ostream & fout) {
	// SimulatedAnnealing sa(vc, ans);
	// sa.workout(fout);
	Genetic ga(vc, ans);
	ga.workout(fout);
}

void TourMan::printPath(std::ostream & fout) {
	int a_pos = 0;
	for (int i = 0; i < ncity; ++i)
	{
		if ( vc[ (*ans)[i] ].getName() == 'A' ) {
			a_pos = i;
			break;
		}
	}

	for (int i = 0; i < ncity; ++i)
	{
		fout << vc[ (*ans)[ (i+a_pos)%ncity ] ].getName();

		if (i + 1 == ncity) {
			// fout << ' ' << cost(*ans) << std::endl;
			printf(" %.3lf\n", cost(*ans));
		} else {
			fout << ' ';
		}
	}
}

double TourMan::cost(const Answer & answer) {
	double dist = 0.0;
	for (int i = 0, j = 1; i < ncity; ++i, ++j)
	{
		if (j == ncity) j = 0;
		dist += vc[ answer[i] ].distanceTo(vc[ answer[j] ]);
	}
	return dist;
}
