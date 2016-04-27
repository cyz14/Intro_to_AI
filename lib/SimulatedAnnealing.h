#ifndef SIMULATEDANNEALING
#define SIMULATEDANNEALING

#include "Answer.h"
#include "city.h"

extern const double min_temp;

class SimulatedAnnealing
{
public:
	SimulatedAnnealing( std::vector<City> & vc, Answer * ans );
	~SimulatedAnnealing();

	void workout(std::ostream &);
	double energy(const Answer & ans);
	double neighbor(const Answer &, Answer &, int , int);
	double dropTemperature(double temperature);
	void printPath(std::ostream &);
	double acceptProbability(double eng, double new_eng, double temperature);
private:
	Answer * m_ans;
	const int ncity;
	std::vector<City> & m_vc;

};

#endif
