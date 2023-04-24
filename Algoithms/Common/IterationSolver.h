#ifndef hpp_IterationSolver_hpp
#define hpp_IterationSolver_hpp

#include "..\..\Interface\ISolver.h"
#include "IterationSolution.h"

class IterationSolver:public ISolver
{
 private:
    void __FreeMemory();
 protected:
    unsigned _uCurrentIteration;
    clock_t  _tBeginTime;
    clock_t  _tEndTime;
 public:
    IterationSolver();
    IterationSolver(const IterationSolver&);
    void operator = (const IterationSolver&);
    virtual ~IterationSolver();

    int iGetCurrentIteration()const;

    float fGetBeginTime_sec();
    float fGetEndTime_sec();
    clock_t tGetBeginTime();
    clock_t tGetEndTime();

    virtual void Iteration (void*,...) = 0;
    virtual bool bTerminate (void*,...) = 0;

	virtual void ViewCurrentState(void*, ...) = 0;

    virtual void Prepare(ISolver*, IterationSolution*);

	virtual SolverResult eSolve(void*,...);


	virtual void Remove();
	virtual void Copy(const void*);
};
#endif
