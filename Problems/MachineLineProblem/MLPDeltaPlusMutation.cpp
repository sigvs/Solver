#include "MLPDeltaPlusMutation.h"
//************************************************************************************************
MLPDeltaPlusMutation::MLPDeltaPlusMutation()
{
};
//************************************************************************************************
MLPDeltaPlusMutation::MLPDeltaPlusMutation(const MLPDeltaPlusMutation& x)
{
	*this=x;
};
//************************************************************************************************
MLPDeltaPlusMutation::~MLPDeltaPlusMutation()
{
};
//************************************************************************************************
void MLPDeltaPlusMutation::operator = (const MLPDeltaPlusMutation& x)
{
	ptDeltaMutation=x.ptDeltaMutation;
};
//************************************************************************************************
SolverResult MLPDeltaPlusMutation::eSolve(void* x_, ...)
 {
    void** x= &x_;
    MLProblem* problem = (MLProblem*)(x[0]);
	EvolutionalAlgorithm* solver = (EvolutionalAlgorithm*)(x[1]);

	for (size_t i = 0; i < solver->pChildren->GetPopulationSize(); i++)
	{
		MLPSolution* Child = (MLPSolution*)(solver->pChildren->pGetIndividPoint(i));

		long UpBound = 0;
		long LowBound = 0;
		long result = 0;
		long ChildSize = Child->GetBufferNumber();

		for (int j = 0; j < ChildSize; j++)
		{
			UpBound = problem->FMachineLine.getBuffer(j + 1)->Volume;
			if (UpBound > (ptDeltaMutation + Child->BufferSize(j)))
				UpBound = ptDeltaMutation + Child->BufferSize(j);
			LowBound = 0;
			if (LowBound < (Child->BufferSize(j) - ptDeltaMutation))
				LowBound = Child->BufferSize(j) - ptDeltaMutation;
			result = LowBound + rand() % (UpBound - LowBound + 1);
			Child->BufferSize(j) = result;
		}

		Child->tTime = (clock() - solver->tGetBeginTime());
		Child->uIterationNumber = solver->iGetCurrentIteration();

		solver->pChildren->pGetIndividPoint(i)->SetValue(problem);
	}

	return SolutionFound; 
 };
//************************************************************************************************
long MLPDeltaPlusMutation::DeltaMutation()const
{
    return ptDeltaMutation;
};
//************************************************************************************************
void MLPDeltaPlusMutation::SetDeltaMutation(long x)
{
    ptDeltaMutation=x;
};
//************************************************************************************************

