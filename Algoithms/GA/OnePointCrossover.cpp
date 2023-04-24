#include "OnePointCrossover.h"
#include <stdlib.h>
//************************************************************************************************
template <typename T>
OnePointCrossover<T>::OnePointCrossover()
{
    ptCrossoverProbability = 0.5;
};
//************************************************************************************************
template <typename T>
OnePointCrossover<T>::OnePointCrossover(const OnePointCrossover& x)
{
    ptCrossoverProbability = 0.5;
	*this=x;
};
//************************************************************************************************
template <typename T>
OnePointCrossover<T>::~OnePointCrossover()
{
};
//************************************************************************************************
template <typename T>
void OnePointCrossover<T>::operator = (const OnePointCrossover& x)
{
	ptCrossoverProbability=x.ptCrossoverProbability;
};
//************************************************************************************************
template <typename T>
SolverResult OnePointCrossover<T>::eSolve(void* x_, ...)
{
    void** x= &x_;
    ISolver* problem = (ISolver*)(x[0]);
    EvolutionalAlgorithm* solver = (EvolutionalAlgorithm*)(x[1]);
    double CrossoverProbability = rand()*1.0/(RAND_MAX*1.0);
    if(CrossoverProbability < ptCrossoverProbability)
    {
        IArray<T>* FirstChild =(IArray<T>*)(solver->pChildren->pGetIndividPoint(0));
        IArray<T>* SecondChild =(IArray<T>*)(solver->pChildren->pGetIndividPoint(1));

        int mixNumber=rand()%FirstChild->GetElementCount();
        int h;

        for(int i=0;i<mixNumber;i++)
        {
            h=FirstChild->GetElement(i);
            FirstChild->SetElement(i,SecondChild->GetElement(i));
            SecondChild->SetElement(i, h);
        }

        solver->pChildren->pGetIndividPoint(0)->SetValue(problem);
        solver->pChildren->pGetIndividPoint(1)->SetValue(problem);
    }
	return SolutionFound;
 };
 //************************************************************************************************
template <typename T>
double OnePointCrossover<T>::CrossoverProbability()const
{
    return ptCrossoverProbability;
};
//************************************************************************************************
template <typename T>
void OnePointCrossover<T>::SetCrossoverProbability(double x)
{
    ptCrossoverProbability=x;
};
//************************************************************************************************
