#include "RandomSelection.h"
#include <stdlib.h>
//************************************************************************************************
RandomSelection::RandomSelection()
{
};
//************************************************************************************************
RandomSelection::RandomSelection(const RandomSelection& x)
{
	*this=x;
};
//************************************************************************************************
RandomSelection::~RandomSelection()
{
};
//************************************************************************************************
void RandomSelection::operator = (const RandomSelection& x)
{
	
};
//************************************************************************************************
 SolverResult RandomSelection::eSolve(void* x_, ...)
 {
    void** x= &x_;
    EvolutionalAlgorithm* solver = (EvolutionalAlgorithm*)(x[1]);
    int newNumber, ChildrenSize;
    ChildrenSize=solver->pChildren->GetPopulationSize();
    for(int i=0;i<ChildrenSize;i++)
    {
		newNumber=rand()%solver->pParents->GetPopulationSize();
        solver->pChildren->pGetIndividPoint(i)->Copy(solver->pParents->pGetIndividPoint(newNumber));
    }
    return SolutionFound;
 };
////************************************************************************************************
// void RandomSelection::Remove()
// {
// };
////************************************************************************************************
// void RandomSelection::Copy(const void* x)
// {
//	 RandomSelection* y = (RandomSelection*)(x);
//	 *this = *y;
// };
////************************************************************************************************
//void* RandomSelection::Clone()const
//{
//      RandomSelection* p = new RandomSelection(*this);
//      return p;
//};
////************************************************************************************************
