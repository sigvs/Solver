#include "IterationTerminator.h"
//************************************************************************************************
IterationTerminator::IterationTerminator()
{
};
//************************************************************************************************
IterationTerminator::IterationTerminator(const IterationTerminator& x)
{
	*this=x;
};
//************************************************************************************************
IterationTerminator::~IterationTerminator()
{
};
//************************************************************************************************
void IterationTerminator::operator = (const IterationTerminator& x)
{
	_iIterationNumber=x._iIterationNumber;
};
//************************************************************************************************
 SolverResult IterationTerminator::eSolve(void* x_, ...)
 {
    void** x= &x_;
    //Solver* problem = (Solver*)(x[0]);
    IterationSolver* solver = (IterationSolver*)(x[1]);
    bool* result=(bool*)(x[2]);
    if(solver->iGetCurrentIteration()>=_iIterationNumber)*result=true;
    else *result=false;
    return SolutionFound;
 };
//************************************************************************************************
int IterationTerminator::iGetIterationNumber()const
{
    return _iIterationNumber;
};
//************************************************************************************************
void IterationTerminator::SetIterationNumber(int x)
{
    _iIterationNumber=x;
};
////************************************************************************************************
// void IterationTerminator::Copy(void* x)
// {
//    IterationTerminator* y = (IterationTerminator*)(x);
//    *this = *y;
// };
////************************************************************************************************
//string IterationTerminator::sTypeName()const
//{
//	return "IterationTerminator";
//};
////************************************************************************************************
//BaseObject* IterationTerminator::pClone()const
//{
//   IterationTerminator* p = new IterationTerminator(*this);
//   return p;
//};
////************************************************************************************************
