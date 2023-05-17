#include "CFLDPMutation.h"
//************************************************************************************************
CFLDPMutation::CFLDPMutation()
{
	_VariantMutation = new CFLDPRandomOpenRandom();
	_DeviationMutation = new CFLDPDeviationDemandMutation();
};
//************************************************************************************************
CFLDPMutation::CFLDPMutation(const CFLDPMutation& x)
{
	*this=x;
};
//************************************************************************************************
CFLDPMutation::~CFLDPMutation()
{
};
//************************************************************************************************
void CFLDPMutation::operator = (const CFLDPMutation& x)
{
	_VariantMutation->operator=(*x._VariantMutation);
	_DeviationMutation->operator=(*x._DeviationMutation);
};
//************************************************************************************************
SolverResult CFLDPMutation::eSolve(void* x_, ...)
 {
    void** x= &x_;
	CFLDProblem* problem = (CFLDProblem*)(x[0]);
	EvolutionalAlgorithm* solver = (EvolutionalAlgorithm*)(x[1]);

	for (size_t i = 0; i < solver->pChildren->GetPopulationSize(); i++)
	{
		CFLDPSolution* Child = (CFLDPSolution*)(solver->pChildren->pGetIndividPoint(i));

		_VariantMutation->eSolve(problem,Child);
		_DeviationMutation->eSolve(problem, Child);

		Child->tTime = (clock() - solver->tGetBeginTime());
		Child->uIterationNumber = solver->iGetCurrentIteration();

		solver->pChildren->pGetIndividPoint(i)->SetValue(problem);
	}

	return SolutionFound; 
 };
//************************************************************************************************
void CFLDPMutation::SetVariantParametr(int p)
{
	_VariantMutation->SetVariantParametr(p);
}
//************************************************************************************************
void CFLDPMutation::SetDeviationDemandMutationParametr(int p)
{
	_DeviationMutation->SetDeviationDemandMutationParametr(p);
}
//************************************************************************************************

