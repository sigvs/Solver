#include "AddPopWorseOrDubDead.h"
//************************************************************************************************
AddPopWorseOrDubDead::AddPopWorseOrDubDead()
{
};
//************************************************************************************************
AddPopWorseOrDubDead::AddPopWorseOrDubDead(const AddPopWorseOrDubDead& x)
{
	*this=x;
};
//************************************************************************************************
AddPopWorseOrDubDead::~AddPopWorseOrDubDead()
{
};
//************************************************************************************************
void AddPopWorseOrDubDead::operator = (const AddPopWorseOrDubDead& x)
{
	ISolver::operator = (x);
};
//************************************************************************************************
SolverResult AddPopWorseOrDubDead::eSolve(void* x_, ...)
{
    void** x= &x_;
    ISolver* problem = (ISolver*)(x[0]);
    GA* solver = (GA*)(x[1]);

    for(unsigned i=0;i<solver->pChildren->GetPopulationSize();i++)
     AddOne(problem, solver, solver->pChildren->pGetIndividPoint(i));

    return SolutionFound;
};
//************************************************************************************************
void AddPopWorseOrDubDead::AddOne(ISolver* problem, GA* solver, Solution* Child)
{
    if(solver->pParents->pWorseSolution->bWorseOrEqual(Child)&& !solver->pParents->bHaveIndivid(Child))
    {
        solver->pParents->pWorseSolution->Copy(Child);
        solver->pParents->SearchBestSolution();
        solver->pParents->SearchWorseSolution();
    }

};
//************************************************************************************************
