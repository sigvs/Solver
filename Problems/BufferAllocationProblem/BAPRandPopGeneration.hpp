#ifndef hpp_tBAPRandPopGeneration_hpp
#define hpp_tBAPRandPopGeneration_hpp

#include "Solver.hpp"
#include "BAPSolution.hpp"
#include "BAPPopulation.hpp"

class tpBAPRandPopGeneration:public tpSolver
{
 public:
  tpBAPRandPopGeneration();
  tpBAPRandPopGeneration(const tpBAPRandPopGeneration&);
  void operator = (const tpBAPRandPopGeneration&);
  virtual ~tpBAPRandPopGeneration();

  virtual void Solve(void*, ...);

  virtual void Copy(void*);
  virtual tpChar* TypeName()const;
};
//************************************************************************************************
tpBAPRandPopGeneration::tpBAPRandPopGeneration()
{
};
//************************************************************************************************
tpBAPRandPopGeneration::tpBAPRandPopGeneration(const tpBAPRandPopGeneration& x)
{
	*this=x;
};
//************************************************************************************************
tpBAPRandPopGeneration::~tpBAPRandPopGeneration()
{
};
//************************************************************************************************
void tpBAPRandPopGeneration::operator = (const tpBAPRandPopGeneration& x)
{
	tpSolver::operator = (x);
};
//************************************************************************************************
void tpBAPRandPopGeneration::Solve(void* x_, ...)
{
    void** x= &x_;
    tpMLProblem* problem = (tpMLProblem*)(x[0]);
    tpGA* solver = (tpGA*)(x[1]);
    tpInt LowBound=0;
    tpInt UpBound=0;
    for(tpIndex i=0;i<solver->Parents->GetSize();i++)
   {
        tpBAPPopulation* bp = (tpBAPPopulation*)solver->Parents;
     	for(tpIndex j=0;j<bp->Individ(i)->GetBufferNumber();j++)
     	{
            UpBound=problem->FMachineLine.Buffer(j+1)->Volume;
            LowBound=0;
            bp->Individ(i)->BufferSize(j)=LowBound+rand()%(UpBound-LowBound+1);
        }
        solver->Parents->GetIndivid(i)->SetValue(problem);
   }
   solver->Parents->GetMinIndexIndivid();
   solver->Parents->GetMaxIndexIndivid();
};
//************************************************************************************************
 void tpBAPRandPopGeneration::Copy(void* x)
 {
    tpBAPRandPopGeneration* y = (tpBAPRandPopGeneration*)(x);
    *this = *y;
 };
//************************************************************************************************
tpChar* tpBAPRandPopGeneration::TypeName()const
{
	return "BAPRandPopGeneration";
};
//************************************************************************************************
#endif
