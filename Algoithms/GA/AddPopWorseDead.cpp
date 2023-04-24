#include "AddPopWorseDead.h"
//************************************************************************************************
AddPopWorseDead::AddPopWorseDead()
{
};
//************************************************************************************************
AddPopWorseDead::AddPopWorseDead(const AddPopWorseDead& x)
{
	*this=x;
};
//************************************************************************************************
AddPopWorseDead::~AddPopWorseDead()
{
};
//************************************************************************************************
void AddPopWorseDead::operator = (const AddPopWorseDead& x)
{
	ISolver::operator = (x);
};
//************************************************************************************************
SolverResult AddPopWorseDead::eSolve(void* x_, ...)
{
    void** x= &x_;
    ISolver* problem = (ISolver*)(x[0]);
    GA* solver = (GA*)(x[1]);

    for(unsigned i=0;i<solver->pChildren->GetPopulationSize();i++)
        AddOne(problem, solver, solver->pChildren->pGetIndividPoint(i));

    return SolutionFound;
};
//************************************************************************************************
void AddPopWorseDead::AddOne(ISolver* problem, GA* solver, Solution* Child)
{
    if(solver->pParents->pWorseSolution->bWorseOrEqual(Child))
    {
     solver->pParents->pWorseSolution->Copy(Child);
     solver->pParents->SearchBestSolution();
     solver->pParents->SearchWorseSolution();
    }
};
