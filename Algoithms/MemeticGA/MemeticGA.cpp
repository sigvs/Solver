#include "MemeticGA.h"
//************************************************************************************************
MemeticGA::MemeticGA()
{
        pLocalOptimization=NULL;
};
//************************************************************************************************
MemeticGA::MemeticGA(const MemeticGA& x)
{
        pLocalOptimization=NULL;
	*this=x;
};
//************************************************************************************************
MemeticGA::~MemeticGA()
{
        pLocalOptimization=NULL;
};
//************************************************************************************************
void MemeticGA::operator = (const MemeticGA& x)
{
    GA::operator = (x);
    pLocalOptimization=x.pLocalOptimization;
};
//************************************************************************************************
void MemeticGA::Iteration(void* x_,...)
{
    void** x= &x_;
    ISolver* _pProblem = (ISolver*)(x[0]);
    //clock_t  tm=clock();
    //clock_t  cur, prev; prev = tm;
    if(pSelection)pSelection->eSolve(_pProblem,this);
    //cur = clock();cout<<"Selection"<<(cur-prev)*1.0/CLOCKS_PER_SEC<<endl;prev=cur;
    if(pCrossover)pCrossover->eSolve(_pProblem,this);
    //cur = clock();cout<<"Crossover"<<(cur-prev)*1.0/CLOCKS_PER_SEC<<endl;prev=cur;
    if(pMutation)pMutation->eSolve(_pProblem,this);
    //cur = clock();cout<<"Mutation"<<(cur-prev)*1.0/CLOCKS_PER_SEC<<endl;prev=cur;
    if(pLocalOptimization)pLocalOptimization->eSolve(_pProblem,this);
    //cur = clock();cout<<"LocalOptimization"<<(cur-prev)*1.0/CLOCKS_PER_SEC<<endl;prev=cur;
    if(pAdder)pAdder->eSolve(_pProblem,this);
    //cur = clock();cout<<"Adder"<<(cur-prev)*1.0/CLOCKS_PER_SEC<<endl;prev=cur;
};
//************************************************************************************************
