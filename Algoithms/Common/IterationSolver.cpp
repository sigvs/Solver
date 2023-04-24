#include "IterationSolver.h"
//************************************************************************************************
IterationSolver::IterationSolver()
{
    _uCurrentIteration=0;
    _tBeginTime=clock();
};
//************************************************************************************************
IterationSolver::IterationSolver(const IterationSolver& x)
{

    _tBeginTime=clock();
    _uCurrentIteration=0;
    *this=x;
};
//************************************************************************************************
void IterationSolver::__FreeMemory()
{
    _uCurrentIteration=0;
    _tBeginTime=0;
};
//************************************************************************************************
IterationSolver::~IterationSolver()
{
  __FreeMemory();
};
//************************************************************************************************
void IterationSolver::operator = (const IterationSolver& x)
{
	_uCurrentIteration=x._uCurrentIteration;
};
//************************************************************************************************
void IterationSolver::Prepare(ISolver* _pProblem, IterationSolution* _pCurrentRecord)
{
    _uCurrentIteration=0;
    _tBeginTime=clock();
    _tEndTime=clock();
};
//************************************************************************************************
SolverResult IterationSolver::eSolve (void* x_, ...)
{
    void** x= &x_;
    ISolver* _pProblem = (ISolver*)(x[0]);
    IterationSolution* _pCurrentRecord = (IterationSolution*)(x[1]);

    Prepare(_pProblem, _pCurrentRecord);

    while(!bTerminate (_pProblem,this))
    {
        _uCurrentIteration++;
        Iteration(_pProblem);
        _tEndTime = clock();
        _pCurrentRecord->tTime=(_tEndTime-_tBeginTime);
        _pCurrentRecord->uIterationNumber=_uCurrentIteration;
    }

    return SolutionFound;
};
//************************************************************************************************
int IterationSolver::iGetCurrentIteration()const
{
	return _uCurrentIteration;
};
//************************************************************************************************
clock_t IterationSolver::tGetBeginTime()
{
  return _tBeginTime;
};
//************************************************************************************************
float IterationSolver::fGetBeginTime_sec()
{
   return _tBeginTime/CLOCKS_PER_SEC;
};
//************************************************************************************************
float IterationSolver::fGetEndTime_sec()
{
   return _tEndTime/CLOCKS_PER_SEC;
};
//************************************************************************************************
 void IterationSolver::Remove()
 {
     __FreeMemory();
 };
//************************************************************************************************
 void IterationSolver::Copy(const void* x)
 {
    IterationSolver* y = (IterationSolver*)(x);
    *this = *y;
 };
//************************************************************************************************
