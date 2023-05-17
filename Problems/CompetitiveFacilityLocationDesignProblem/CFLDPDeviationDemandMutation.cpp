#include "CFLDPDeviationDemandMutation.h"
//************************************************************************************************
CFLDPDeviationDemandMutation::CFLDPDeviationDemandMutation()
{
};
//************************************************************************************************
CFLDPDeviationDemandMutation::CFLDPDeviationDemandMutation(const CFLDPDeviationDemandMutation& x)
{
	*this=x;
};
//************************************************************************************************
CFLDPDeviationDemandMutation::~CFLDPDeviationDemandMutation()
{
};
//************************************************************************************************
void CFLDPDeviationDemandMutation::operator = (const CFLDPDeviationDemandMutation& x)
{
	_k=x._k;
};
//************************************************************************************************
void CFLDPDeviationDemandMutation::SetDeviationDemandMutationParametr(int p)
{
	_k = p;
}

//************************************************************************************************
SolverResult CFLDPDeviationDemandMutation::eSolve(void* x_, ...)
 {
    void** x= &x_;
	CFLDProblem* problem = (CFLDProblem*)(x[0]);
	CFLDPSolution* solution = (CFLDPSolution*)(x[1]);

	iVector index;
	index.resize(problem->getN());
	for (int i = 0; i < problem->getN(); ++i) index[i] = i;

	int p = _k;
	if (p > problem->getN()) p = problem->getN();

	for (int i = 0; i < p; ++i) {
		int rnd = uniform(0, index.size()-1);
		int ind = index[rnd];

		if (solution->DeviationDemand(ind) == 0)
		{
			solution->DeviationDemand(ind) = 1;
		}
		else
		{
			if (solution->DeviationDemand(ind) == 1)
			{
				auto r = uniform();
				if (r > 0.001)
				{
					if(solution->DeviationDemand(ind) < problem->getw(ind))
						solution->DeviationDemand(ind) += 1;
				}
				else solution->DeviationDemand(ind) = 0;
			}
			else
			{
				if (solution->DeviationDemand(ind) > 1 && solution->DeviationDemand(ind) < problem->getw(ind) - 1)
				{
					auto r = uniform();
					if (r > 0.1) solution->DeviationDemand(ind) -= 1;
					else solution->DeviationDemand(ind) += 1;
				}
				else
				{
					if (solution->DeviationDemand(ind) == problem->getw(ind))
					{
						auto r = uniform();
						if (r > 0.1) solution->DeviationDemand(ind) -= 1;
					}
				}
			}
		}

		auto pointer = index.cbegin() + rnd; // указатель на первый элемент
		index.erase(pointer, pointer+1); // удаляем с третьего элемента до последнего
	}

	index.clear();
	return SolutionFound; 
 };
//************************************************************************************************
int CFLDPDeviationDemandMutation::uniform(int a, int b)
{
	return a + std::rand() % (b - a + 1);
}
//************************************************************************************************
double CFLDPDeviationDemandMutation::uniform()
{
	return std::rand()*1.0 / RAND_MAX;
}
//************************************************************************************************
