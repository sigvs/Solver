#include "NSGA2PopulationAdder.h"
//************************************************************************************************
NSGA2PopulationAdder::NSGA2PopulationAdder()
{
};
//************************************************************************************************
NSGA2PopulationAdder::NSGA2PopulationAdder(const NSGA2PopulationAdder& x)
{
	*this=x;
};
//************************************************************************************************
NSGA2PopulationAdder::~NSGA2PopulationAdder()
{
};
//************************************************************************************************
void NSGA2PopulationAdder::operator = (const NSGA2PopulationAdder& x)
{
};
//************************************************************************************************
SolverResult NSGA2PopulationAdder::eSolve(void* x_, ...)
{
    void** x= &x_;
    MLProblem* problem = (MLProblem*)(x[0]);
    GA* solver = (GA*)(x[1]);
	NSGA2Population* p = (NSGA2Population*)solver->pParents;
	p->AddChildIndivids(solver->pChildren);

    return SolutionFound;
};
//************************************************************************************************
