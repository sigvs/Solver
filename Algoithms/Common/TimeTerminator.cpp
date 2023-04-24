#include "TimeTerminator.h"
//************************************************************************************************
TimeTerminator::TimeTerminator()
{
};
//************************************************************************************************
TimeTerminator::TimeTerminator(const TimeTerminator& x)
{
	*this=x;
};
//************************************************************************************************
TimeTerminator::~TimeTerminator()
{
};
//************************************************************************************************
void TimeTerminator::operator = (const TimeTerminator& x)
{
	_fTime=x._fTime;
};
//************************************************************************************************
 SolverResult TimeTerminator::eSolve(void* x_, ...)
 {
    void** x= &x_;
    //Solver* problem = (Solver*)(x[0]);
    IterationSolver* solver = (IterationSolver*)(x[1]);
    bool* result=(bool*)(x[2]);
    float timeleft =(1.0*clock()-1.0*solver->tGetBeginTime())/CLOCKS_PER_SEC;
    if(timeleft>=_fTime)*result=true;
    else *result=false;
    return SolutionFound;
 };
//************************************************************************************************
float TimeTerminator::fGetTime_sec()const
{
    return _fTime;
};
//************************************************************************************************
void TimeTerminator::SetTime_sec(float x)
{
    _fTime=x;
};
////************************************************************************************************
// void TimeTerminator::Copy(const void* x)
// {
//    TimeTerminator* y = (TimeTerminator*)(x);
//    *this = *y;
// };
////************************************************************************************************
//void TimeTerminator::Remove() 
//{
//};
////************************************************************************************************
//void* TimeTerminator::Clone()const
//{
//
//   TimeTerminator* p = new TimeTerminator(*this);
//   return p;
//};
////************************************************************************************************
