#ifndef hpp_tBAPWhileGood_hpp
#define hpp_tBAPWhileGood_hpp

#include "MLProblem.hpp"
#include "BAPSolution.hpp"

class tpBAPWhileGood:public tpSolver
{
 protected:
  tpIndex* ptOrder;
  tpBAPSolution ptRecordNext;
  tpIndex ptIterationNumber;
 public:
  tpBAPWhileGood();
  tpBAPWhileGood(const tpBAPWhileGood&);
  void operator = (const tpBAPWhileGood&);
  virtual ~tpBAPWhileGood();

  virtual void SetSize(tpIndex);

  void SetIterationNumber(tpIndex);
  tpIndex GetIterationNumber();

  void FreeMemory();

  virtual void Solve(void*, ...);

  virtual void FreeAllMemory();
  virtual void Copy(void*);
  virtual tpChar* TypeName()const;
};
//************************************************************************************************
tpBAPWhileGood::tpBAPWhileGood()
{
    ptOrder=NULL;
    ptIterationNumber=0;
};
//************************************************************************************************
tpBAPWhileGood::tpBAPWhileGood(const tpBAPWhileGood& x)
{
    ptOrder=NULL;
    ptIterationNumber=0;
	*this=x;
};
//************************************************************************************************
tpBAPWhileGood::~tpBAPWhileGood()
{
    FreeMemory();
};
//************************************************************************************************
void tpBAPWhileGood::operator = (const tpBAPWhileGood& x)
{
    tpSolver::operator = (x);
    if(ptRecordNext.GetBufferNumber()!=x.ptRecordNext.GetBufferNumber())SetSize(x.ptRecordNext.GetBufferNumber());
    for(tpIndex i=0;i<ptRecordNext.GetBufferNumber();i++)
        ptOrder[i]=x.ptOrder[i];
    ptRecordNext=x.ptRecordNext;
    ptIterationNumber=x.ptIterationNumber;
};
//************************************************************************************************
void tpBAPWhileGood::FreeMemory()
{
        if(ptOrder)delete[] ptOrder;
        ptOrder=NULL;
        ptRecordNext.FreeMemory();
};
//************************************************************************************************
void tpBAPWhileGood::SetSize(tpIndex x)
{
        if(ptOrder)delete[] ptOrder;
        ptOrder=NULL;
        ptOrder= new tpIndex[x];
        ptRecordNext.SetBufferNumber(x);
};
//************************************************************************************************
void tpBAPWhileGood::Solve(void* x_, ...)
 {
    void** x= &x_;
    tpMLProblem* problem = (tpMLProblem*)(x[0]);
    tpGA* solver = (tpGA*)(x[1]);
    tpReal temp;

  if (ptIterationNumber != 0 && modf((solver->CurrentIteration()*1.0)/(ptIterationNumber*1.0),&temp)==0)
  {

    tpBAPSolution* FirstChild =(tpBAPSolution*)(solver->Children->GetIndivid(0));
    tpBAPSolution* SecondChild =(tpBAPSolution*)(solver->Children->GetIndivid(1));

    tpInt UpBound=0;
    tpInt LowBound=0;
    tpIndex num, ChildSize;
    tpBool flag;

    ChildSize = FirstChild->GetBufferNumber();
    for(tpIndex i=0;i<ChildSize;i++)
    {
        num=rand()%ChildSize;
        while(1)
        {
                flag=false;
                for(tpIndex j=0;j<i;j++)
                        if(ptOrder[j]==num)flag=true;
                                if(flag)
                                {
                                        num++;
                                        if(num==ChildSize)num=0;
                                }
                                else
                                {
                                        ptOrder[i]=num;
                                        break;
                                }
        }

    }

    for(tpIndex i=0;i<ChildSize;i++)
    {
        num=ptOrder[i];

        UpBound=problem->FMachineLine.Buffer(num+1)->Volume;
        LowBound=0;
        ptRecordNext.Copy(FirstChild);
        while(1)
        {
            if(FirstChild->BufferSize(num)+1 > UpBound)break;
            ptRecordNext.BufferSize(num)=FirstChild->BufferSize(num)+1;
            ptRecordNext.SetValue(problem);
            if(FirstChild->Better(&ptRecordNext))break;
            FirstChild->Copy(&ptRecordNext);
        }
        while(1)
        {
            if(FirstChild->BufferSize(num)-1 < LowBound)break;
            ptRecordNext.BufferSize(num)=FirstChild->BufferSize(num)-1;
            ptRecordNext.SetValue(problem);
            if(FirstChild->Better(&ptRecordNext))break;
            FirstChild->Copy(&ptRecordNext);
        }
    }

    for(tpIndex i=0;i<ChildSize;i++)
    {
        num=ptOrder[i];
        UpBound=problem->FMachineLine.Buffer(num+1)->Volume;
        LowBound=0;
        ptRecordNext.Copy(SecondChild);
        while(1)
        {
            if(SecondChild->BufferSize(num)+1 > UpBound)break;
            ptRecordNext.BufferSize(num)=SecondChild->BufferSize(num)+1;
            ptRecordNext.SetValue(problem);
            if(SecondChild->Better(&ptRecordNext))break;
            SecondChild->Copy(&ptRecordNext);
        }
        while(1)
        {
            if(SecondChild->BufferSize(num)-1 < LowBound)break;
            ptRecordNext.BufferSize(num)=SecondChild->BufferSize(num)-1;
            ptRecordNext.SetValue(problem);
            if(SecondChild->Better(&ptRecordNext))break;
            SecondChild->Copy(&ptRecordNext);
        }
    }
  }
 };
//************************************************************************************************
void tpBAPWhileGood::SetIterationNumber(tpIndex x)
{
    ptIterationNumber=x;
};
//************************************************************************************************
tpIndex tpBAPWhileGood::GetIterationNumber()
{
    return ptIterationNumber;
};
//************************************************************************************************
void tpBAPWhileGood::FreeAllMemory()
{
    FreeMemory();
    tpSolver::FreeAllMemory();
};
//************************************************************************************************
void tpBAPWhileGood::Copy(void* x)
 {
    tpBAPWhileGood* y = (tpBAPWhileGood*)(x);
    *this = *y;
 };
//************************************************************************************************
tpChar* tpBAPWhileGood::TypeName()const
{
	return "BAPWhileGood";
};
//************************************************************************************************
#endif
