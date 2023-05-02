#include "CFLDPRandomOpenRandom.h"
//************************************************************************************************
CFLDPRandomOpenRandom::CFLDPRandomOpenRandom()
{
};
//************************************************************************************************
CFLDPRandomOpenRandom::CFLDPRandomOpenRandom(const CFLDPRandomOpenRandom& x)
{
	*this=x;
};
//************************************************************************************************
CFLDPRandomOpenRandom::~CFLDPRandomOpenRandom()
{
};
//************************************************************************************************
void CFLDPRandomOpenRandom::operator = (const CFLDPRandomOpenRandom& x)
{
	_S=x._S;
};
//************************************************************************************************
SolverResult CFLDPRandomOpenRandom::eSolve(void* x_, ...)
 {
    void** x= &x_;
	CFLDProblem* problem = (CFLDProblem*)(x[0]);
	EvolutionalAlgorithm* solver = (EvolutionalAlgorithm*)(x[1]);

	for (size_t i = 0; i < solver->pChildren->GetPopulationSize(); i++)
	{
		CFLDPSolution* Child = (CFLDPSolution*)(solver->pChildren->pGetIndividPoint(i));

		next(Child);

		Child->tTime = (clock() - solver->tGetBeginTime());
		Child->uIterationNumber = solver->iGetCurrentIteration();

		solver->pChildren->pGetIndividPoint(i)->SetValue(problem);
	}

	return SolutionFound; 
 };
//************************************************************************************************
int CFLDPRandomOpenRandom::uniform(int a, int b)
{
	return a + std::rand() % (b - a + 1);
}
//************************************************************************************************
void CFLDPRandomOpenRandom::SetS(int p)
{
	_S = p;
}
//************************************************************************************************
bool CFLDPRandomOpenRandom::next(CFLDPSolution* s)
{
	iVector openable;
	for (int i = 0; i < _S; ++i) {
		if (s->DesignVariant(i) < 3) {
			openable.push_back(i);
		}
	}
	if (openable.empty()) {
		return false;
	}
	iVector closeable;
	for (int i = 0; i < _S; ++i) {
		if (s->DesignVariant(i) > 0) {
			closeable.push_back(i);
		}
	}
	if (closeable.empty()) {
		return false;
	}
	__close = closeable[std::rand() % closeable.size()];
	__open = openable[std::rand() % openable.size()];
	__dr = uniform(1, std::min(s->DesignVariant(__close), 3 - s->DesignVariant(__open)));
	s->DesignVariant(__close) -= __dr;
	s->DesignVariant(__open) += __dr;
	return true;
}