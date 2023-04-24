#include "EvolutionalAlgorithm.h"
#include <iostream>
//************************************************************************************************
EvolutionalAlgorithm::EvolutionalAlgorithm()
{
    pParents=NULL;
    pChildren=NULL;
    pSelection=NULL;
    pAdder=NULL;
    pTerminator=NULL;
};
//************************************************************************************************
EvolutionalAlgorithm::EvolutionalAlgorithm(const EvolutionalAlgorithm& x)
{
    pParents=NULL;
    pChildren=NULL;
    pSelection=NULL;
	pMutation=NULL;
    pAdder=NULL;
    pTerminator=NULL;
	*this=x;
};
//************************************************************************************************
EvolutionalAlgorithm::~EvolutionalAlgorithm()
{
};
//************************************************************************************************
void EvolutionalAlgorithm::operator = (const EvolutionalAlgorithm& x)
{
    IterationSolver::operator = (x);
    pParents=x.pParents;
    pChildren=x.pChildren;
    pSelection=x.pSelection;
    pMutation = x.pMutation;
    pAdder=x.pAdder;
    pTerminator=x.pTerminator;
};
//************************************************************************************************
SolverResult EvolutionalAlgorithm::eSolve(void* x_,...)
{
    void** x= &x_;
    ISolver* _pProblem = (ISolver*)(x[0]);

    _uCurrentIteration=0;

	int  NewTime;
    _tBeginTime=clock();
    do
    {
                _uCurrentIteration++;
				//ViewCurrentState("begin iteration");
                Iteration(_pProblem);
				//ViewCurrentState("end iteration");

    }while(bTerminate(_pProblem)==false);

	//ViewCurrentState("end algorithm");

    return SolutionFound;
};
//************************************************************************************************
void EvolutionalAlgorithm::Iteration(void* x_,...)
{
    void** x= &x_;
    ISolver* _pProblem = (ISolver*)(x[0]);
    if(pSelection)pSelection->eSolve(_pProblem,this);
	//ViewCurrentState("after selection");
	if(pMutation)pMutation->eSolve(_pProblem, this);
    if(pAdder)pAdder->eSolve(_pProblem,this);
	//ViewCurrentState("after add");
};
//************************************************************************************************
bool EvolutionalAlgorithm::bTerminate(void* x_,...)
{
    void** x= &x_;
    ISolver* _pProblem = (ISolver*)(x[0]);

    bool temp;
    pTerminator->eSolve(_pProblem,this,&temp);
    return temp;
};
//************************************************************************************************
void EvolutionalAlgorithm::ViewCurrentState(void*, ...)
{
    //cout >> this->iGetCurrentIteration() >>";">> this->pParents->GetPopulationSize();
}
//************************************************************************************************