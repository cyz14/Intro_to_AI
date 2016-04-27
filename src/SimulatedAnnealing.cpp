
#include "../lib/Answer.h"
#include "../lib/SimulatedAnnealing.h"
#include <cassert>
#include <cmath>
#include <iomanip>

#define SA SimulatedAnnealing

const double Tmax = 280;
extern const double min_temp = 1e-3;
const int TIMES_EVERY_TEMP = 100;
const double COOLING_RATE = 0.95;

SA::SA( std::vector<City> & vc, Answer * ans )
	: m_vc(vc), m_ans(ans), ncity(vc.size())
{}

SA::~SA() {}

void SA::workout(std::ostream & fout) {
	Answer curs(m_vc.size());
	curs.random();

	int k = 0;
	double cur_temp = Tmax;
	double cur_eng  = energy(curs);
	double last_eng = 0.0;

	int last_u = 0;
	int last_v = 0;

	while (cur_temp > min_temp) {
		int t_step = 0;
		while (1) {
			if (t_step >= TIMES_EVERY_TEMP * ncity) {
				break;
			}

			Answer neib(ncity);
			int u = 0, v = 0;
			neib.randomUV(u, v, last_u, last_v);
			last_u = u, last_v = v;
			double de = neighbor(curs, neib, u, v);

			double new_eng = energy(neib);

			if (new_eng < cur_eng
				|| neib.rand_0_1() < acceptProbability(cur_eng, new_eng, cur_temp))
			{
				curs = neib;
				last_eng = cur_eng;
				cur_eng = new_eng;
				++k;
				++t_step;
				continue;
			}
		} // end while (1) at this temperature
		cur_temp = dropTemperature(cur_temp);
		(*m_ans) = curs;
		printPath(fout);
		if (cur_temp < min_temp && cur_eng == last_eng) {
			printf("Last temperature: %.3lf\n", cur_temp);
			break;
		}

		last_eng = cur_eng;
	} // not cold enough
} // end workout()

double SA::energy(const Answer & ans) {
	double dist = 0.0;
	for (int i = 0, j = 1; i < ncity; ++i, ++j)
	{
		if (j == ncity) j = 0;
		dist += m_vc[ ans[i] ].distanceTo(m_vc[ ans[j] ]);
	}
	return dist;
}

double SA::neighbor(const Answer & from, Answer & to, int u, int v)
{
	int nc = from.size();
	assert(u != v);
	if (u < v) {
		for (int i = 0; i < nc; ++i)
		{
			if (i <= u || i >= v) {
				to.setAt(i, from[i]);
			} else {
				to.setAt(i, from[u+v-i]);
			}
		}

		return m_vc[ from[u] ].distanceTo(m_vc[ from[v-1] ])
				 + m_vc[ from[u+1] ].distanceTo(m_vc[ from[v] ])
				 - m_vc[ from[u] ].distanceTo(m_vc[ from[u+1] ])
				 - m_vc[ from[v-1] ].distanceTo(m_vc[ from[v] ]);

	} else { // v < u
		for (int i = 0; i < nc; ++i)
		{
			if (v <= i && i <= u) {
				to.setAt(i, from[i]);
			} else {
				int tmp = u + v - i;
				if (tmp >= nc) tmp -= nc;
				else if (tmp < 0) tmp += nc;

				to.setAt(i, from[tmp]);
			}
		}

		return m_vc[from[ (u+1)%nc ]].distanceTo( from[v] )
			+ m_vc[ from[ (v-1+nc)%nc ] ].distanceTo( from[u] )
			- m_vc[ from[ (v-1+nc)%nc ] ].distanceTo( from[v] )
			- m_vc[ from[u] ].distanceTo( from[ (u+1)%nc ] );
		}
}

double SA::acceptProbability(double eng, double new_eng, double temperature)
{
	if (new_eng <= eng) {
		return 1.0;
	}
	return exp( (eng - new_eng) / temperature);
}

double SA::dropTemperature(double temperature)
{
		return COOLING_RATE * temperature;
}

/*
 print the path of current Answer: m_ans
 */
void SA::printPath(std::ostream & fout) {
	int a_pos = 0;
	for (int i = 0; i < ncity; ++i)
	{
		if ( m_vc[ (*m_ans)[i] ].getName() == 'A' ) {
			a_pos = i;
			break;
		}
	}

	for (int i = 0; i < ncity; ++i)
	{
		fout << m_vc[ (*m_ans)[ (i+a_pos)%ncity ] ].getName();

		fout << ' ';
		if (i + 1 == ncity) {
			 fout << std::setprecision(4) << energy(*m_ans) << std::endl;
			// printf("%.3lf\n", energy(*m_ans));
		}
	}
}
