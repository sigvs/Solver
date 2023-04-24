#ifndef hpp_BAPLocalDescent_hpp
#define hpp_BAPLocalDescent_hpp

#include "IterationSolver.hpp"
#include "BAPSolution.hpp"

class tpBAPLocalDescent:public tpIterationSolver
{
 protected:
  tpBAPSolution ptNewRecord;
  tpBAPSolution ptOldRecord;
  tpBAPSolution ptRecord;
 public:
  tpBAPLocalDescent();
  tpBAPLocalDescent(const tpBAPLocalDescent&);
  void operator = (const tpBAPLocalDescent&);
  virtual ~tpBAPLocalDescent();

  virtual void Solve(void*,...);
  virtual void Iteration(tpSolver*);
  virtual tpBool Termination(tpSolver*);
  virtual tpIterationSolution* Record();

  virtual void Generation(tpMLProblem*);

  virtual void SetSize(tpIndex);
  virtual tpIndex GetSize()const;

  void FreeMemory();

  virtual void FreeAllMemory();
  virtual void Copy(void*);
  virtual tpChar* TypeName()const;
};
//************************************************************************************************
tpBAPLocalDescent::tpBAPLocalDescent()
{
};
//************************************************************************************************
tpBAPLocalDescent::tpBAPLocalDescent(const tpBAPLocalDescent& x)
{
	*this=x;
};
//************************************************************************************************
tpBAPLocalDescent::~tpBAPLocalDescent()
{
    FreeMemory();
};
//************************************************************************************************
void tpBAPLocalDescent::operator = (const tpBAPLocalDescent& x)
{
	tpIterationSolver::operator = (x);
	ptNewRecord=x.ptNewRecord;
	ptOldRecord=x.ptOldRecord;
	ptRecord=x.ptRecord;
};
//************************************************************************************************
void tpBAPLocalDescent::Solve (void* x_, ...)
{
    void** x= &x_;
    tpMLProblem* p = (tpMLProblem*)(x[0]);
    tpIterationSolution* r = (tpIterationSolution*)(x[1]);

	Generation(p);

    ptCurrentIteration=0;

    tpInt  OldTime, NewTime;
    OldTime=clock();
    do
    {
                ptCurrentIteration++;
                Iteration(p);
    }while(Termination(p)==false);
    NewTime=clock();

    r->Copy(Record());
//    r->SolvingTime=(NewTime-OldTime)*1.0/CLK_TCK;
    r->IterationNumber=ptCurrentIteration;
};
//************************************************************************************************
void tpBAPLocalDescent::Generation(tpMLProblem* p)
{
    tpInt LowBound=0;
    tpInt UpBound=0;
	for(tpIndex i=0;i<ptNewRecord.GetBufferNumber();i++)
    {
	   UpBound=p->FMachineLine.Buffer(i+1)->Volume;
       LowBound=0;
       ptNewRecord.BufferSize(i)=LowBound+rand()%(UpBound-LowBound+1);
    }
    ptNewRecord.SetValue(p);
};
//************************************************************************************************
void tpBAPLocalDescent::SetSize(tpIndex x)
{
	ptOldRecord.SetBufferNumber(x);
	ptNewRecord.SetBufferNumber(x);
	ptRecord.SetBufferNumber(x);
};
//************************************************************************************************
tpIndex tpBAPLocalDescent::GetSize()const
{
	return ptNewRecord.GetBufferNumber();
};
//************************************************************************************************
void tpBAPLocalDescent::FreeMemory()
{
  ptNewRecord.FreeAllMemory();
  ptOldRecord.FreeAllMemory();
  ptRecord.FreeAllMemory();
};
//************************************************************************************************
void tpBAPLocalDescent::Iteration(tpSolver* p_)
{
	tpMLProblem* p =(tpMLProblem*)(p_);
	ptOldRecord=ptNewRecord;
	ptRecord=ptNewRecord;
    tpInt LowBound=0;
    tpInt UpBound=0;
	for(tpIndex i=0;i<ptOldRecord.GetBufferNumber();i++)
	{
	   UpBound=p->FMachineLine.Buffer(i+1)->Volume;
       LowBound=0;

	   if(ptNewRecord.BufferSize(i)+1<=UpBound)
	   {
		    ptRecord.BufferSize(i)=ptNewRecord.BufferSize(i)+1;
			ptRecord.SetValue(p);
			if(ptRecord.Better(&ptNewRecord))ptNewRecord=ptRecord;
			ptRecord.BufferSize(i)=ptRecord.BufferSize(i)-1;
	   }

	   if(ptNewRecord.BufferSize(i)-1>=LowBound)
	   {
		    ptRecord.BufferSize(i)=ptNewRecord.BufferSize(i)-1;
			ptRecord.SetValue(p);
			if(ptRecord.Better(&ptNewRecord))ptNewRecord=ptRecord;
			ptRecord.BufferSize(i)=ptRecord.BufferSize(i)+1;
	   }


	};
};
//************************************************************************************************
tpBool tpBAPLocalDescent::Termination(tpSolver* p_)
{
	if(ptOldRecord.Equal(&ptNewRecord))return true;
	else return false;
};
//************************************************************************************************
tpIterationSolution* tpBAPLocalDescent::Record()
{
	return &ptNewRecord;
};
//************************************************************************************************
//dopolnenie
//************************************************************************************************
void tpBAPLocalDescent::FreeAllMemory()
{
  FreeMemory();
  tpIterationSolver::FreeAllMemory();
};
//************************************************************************************************
 void tpBAPLocalDescent::Copy(void* x)
 {
    tpBAPLocalDescent* y = (tpBAPLocalDescent*)(x);
    *this = *y;
 };
//************************************************************************************************
tpChar* tpBAPLocalDescent::TypeName()const
{
	return "BAPLocalDescent";
};
//************************************************************************************************
#endif
