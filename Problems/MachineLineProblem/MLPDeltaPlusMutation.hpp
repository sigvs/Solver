#ifndef hpp_tBAPDeltaPlusMutation_hpp
#define hpp_tBAPDeltaPlusMutation_hpp

#include "Var.hpp"
#include "MLProblem.hpp"
#include "BAPSolution.hpp"


class tpBAPDeltaPlusMutation:public tpSolver
{
 protected:
  tpInt ptDeltaMutation;
 public:
  tpBAPDeltaPlusMutation();
  tpBAPDeltaPlusMutation(const tpBAPDeltaPlusMutation&);
  void operator = (const tpBAPDeltaPlusMutation&);
  virtual ~tpBAPDeltaPlusMutation();

  virtual void Solve(void*, ...);

  tpInt DeltaMutation()const;
  void SetDeltaMutation(tpInt);

  virtual void Copy(void*);
  virtual tpChar* TypeName()const;
};
//************************************************************************************************
tpBAPDeltaPlusMutation::tpBAPDeltaPlusMutation()
{
};
//************************************************************************************************
tpBAPDeltaPlusMutation::tpBAPDeltaPlusMutation(const tpBAPDeltaPlusMutation& x)
{
	*this=x;
};
//************************************************************************************************
tpBAPDeltaPlusMutation::~tpBAPDeltaPlusMutation()
{
};
//************************************************************************************************
void tpBAPDeltaPlusMutation::operator = (const tpBAPDeltaPlusMutation& x)
{
	tpSolver::operator = (x);
	ptDeltaMutation=x.ptDeltaMutation;
};
//************************************************************************************************
void tpBAPDeltaPlusMutation::Solve(void* x_, ...)
 {
    void** x= &x_;
    tpMLProblem* problem = (tpMLProblem*)(x[0]);
    tpGA* solver = (tpGA*)(x[1]);

    tpBAPSolution* FirstChild =(tpBAPSolution*)(solver->Children->GetIndivid(0));
    tpBAPSolution* SecondChild =(tpBAPSolution*)(solver->Children->GetIndivid(1));

    tpInt UpBound=0;
    tpInt LowBound=0;
    tpInt result=0;
    tpIndex ChildSize=FirstChild->GetBufferNumber();

    for(tpIndex i=0;i<ChildSize;i++)
    {
        UpBound=problem->FMachineLine.Buffer(i+1)->Volume;
        if(UpBound>(ptDeltaMutation+FirstChild->BufferSize(i)))
            UpBound=ptDeltaMutation+FirstChild->BufferSize(i);
        LowBound=0;
        if(LowBound<(FirstChild->BufferSize(i)-ptDeltaMutation))
            LowBound=FirstChild->BufferSize(i)-ptDeltaMutation;
        result=LowBound+rand()%(UpBound-LowBound+1);
        FirstChild->BufferSize(i)=result;
    }
    ChildSize=SecondChild->GetBufferNumber();
    for(tpIndex i=0;i<ChildSize;i++)
    {
        UpBound=problem->FMachineLine.Buffer(i+1)->Volume;
        if(UpBound>(ptDeltaMutation+SecondChild->BufferSize(i)))
            UpBound=ptDeltaMutation+SecondChild->BufferSize(i);
        LowBound=0;
        if(LowBound<(SecondChild->BufferSize(i)-ptDeltaMutation))
            LowBound=SecondChild->BufferSize(i)-ptDeltaMutation;
        result=LowBound+rand()%(UpBound-LowBound+1);
        SecondChild->BufferSize(i)=result;
    }


    solver->Children->GetIndivid(0)->SetValue(problem);
    solver->Children->GetIndivid(1)->SetValue(problem);
 };
//************************************************************************************************
tpInt tpBAPDeltaPlusMutation::DeltaMutation()const
{
    return ptDeltaMutation;
};
//************************************************************************************************
void tpBAPDeltaPlusMutation::SetDeltaMutation(tpInt x)
{
    ptDeltaMutation=x;
};
//************************************************************************************************
void tpBAPDeltaPlusMutation::Copy(void* x)
 {
    tpBAPDeltaPlusMutation* y = (tpBAPDeltaPlusMutation*)(x);
    *this = *y;
 };
//************************************************************************************************
tpChar* tpBAPDeltaPlusMutation::TypeName()const
{
	return "BAPDeltaPlusMutation";
};
//************************************************************************************************
#endif
