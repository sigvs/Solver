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
	CFLDPSolution* solution = (CFLDPSolution*)(x[1]);

	next(problem,solution);

	return SolutionFound; 
 };
//************************************************************************************************
int CFLDPRandomOpenRandom::uniform(int a, int b)
{
	return a + std::rand() % (b - a + 1);
}
//************************************************************************************************
void CFLDPRandomOpenRandom::SetVariantParametr(int p)
{
	_S = p;
}
//************************************************************************************************
bool CFLDPRandomOpenRandom::next(CFLDProblem* problem, CFLDPSolution* s)
{
	iVector openable;
	for (int i = 0; i < _S; ++i) {
		int ind = problem->getIndex()[i];
		if (s->DesignVariant(ind) < 3) {
			openable.push_back(ind);
		}
	}
	if (openable.empty()) {
		return false;
	}
	iVector closeable;
	for (int i = 0; i < _S; ++i) {
		int ind = problem->getIndex()[i];
		if (s->DesignVariant(ind) > 0) {
			closeable.push_back(ind);
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
//************************************************************************************************