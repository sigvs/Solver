#include "IncreasePopulationIfNotWorse.h"
//************************************************************************************************
IncreasePopulationIfNotWorse::IncreasePopulationIfNotWorse()
{
};
//************************************************************************************************
IncreasePopulationIfNotWorse::IncreasePopulationIfNotWorse(const IncreasePopulationIfNotWorse& x)
{
	*this=x;
};
//************************************************************************************************
IncreasePopulationIfNotWorse::~IncreasePopulationIfNotWorse()
{
};
//************************************************************************************************
void IncreasePopulationIfNotWorse::operator = (const IncreasePopulationIfNotWorse& x)
{
};
//************************************************************************************************
SolverResult IncreasePopulationIfNotWorse::eSolve(void* x_, ...)
{
    void** x= &x_;
    ISolver* problem = (ISolver*)(x[0]);
    EvolutionalAlgorithm* solver = (EvolutionalAlgorithm*)(x[1]);

    for(unsigned i=0;i<solver->pChildren->GetPopulationSize();i++)
        AddOne(problem, solver->pParents , solver->pChildren->pGetIndividPoint(i));

    return SolutionFound;
};
//************************************************************************************************
void IncreasePopulationIfNotWorse::AddOne(ISolver* problem, Population* pop, Solution* Child)
{
	if(!pop->bHaveIndivid(Child))
	{
		bool b = true;
		int i = pop->GetPopulationSize()-1;
		Solution* sol = pop->pGetIndividPoint(i);
		while(true)
		{
			if(Child->bWorseOrEqual(sol))
			{
				b = false;
				break;
			}

			if( Child->bBetterOrEqual(sol))	
				pop->RemoveIndividByIndex(i);
			i--;
			if(i<0)break;
		}
		if(b)
			pop->AppendIndivid(Child);

	}
};
////************************************************************************************************
//void* IncreasePopulationIfNotWorse::Clone()const
//{
//     IncreasePopulationIfNotWorse* p = new IncreasePopulationIfNotWorse(*this);
//     return p;
//};
////************************************************************************************************
//void IncreasePopulationIfNotWorse::Remove()
//{
//};
////************************************************************************************************
//void IncreasePopulationIfNotWorse::Copy(const void*)
//{
//};
////************************************************************************************************
