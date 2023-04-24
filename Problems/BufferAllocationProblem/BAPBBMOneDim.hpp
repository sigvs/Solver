#ifndef hpp_BAPBBMOneDim_hpp
#define hpp_BAPBBMOneDim_hpp

#include "BBM.hpp"
#include "GA.hpp"
#include "BAPSolution.hpp"
#include "MLProblem.hpp"

class tpBAPBBMOneDim:public tpBBM
{
 protected:
	 tpIndex* ptOrder;
	 tpIndex ptSize;

     tpReal* ptMaxProfitValue;
     tpReal* ptMinInputsValue;

	 tpInt* ptMaxBufferSize;
	 tpInt* ptMinBufferSize;

	 tpIndex ptCurrentIndexSet;
	 tpIndex ptMaxIndexSet;
	 tpIndex ptCurrentBufferIndex;

	 tpBAPSolution* ptCurrentChild;

	 tpBool ptMaxProfitValueFlag;
	 tpBool ptMinInputsValueFlag;

	 void GetMaxProfitValue(tpMLProblem*);
    void GetMinInputsValue(tpMLProblem*);
 public:
  tpBAPBBMOneDim();
  tpBAPBBMOneDim(const tpBAPBBMOneDim&);
  void operator = (const tpBAPBBMOneDim&);
  virtual ~tpBAPBBMOneDim();

  virtual void Solve(void*,...);
  virtual void Branching(tpSolver*);
  virtual void Bounding(tpSolver*);
  virtual tpBool NotBranched(tpSolver*);

  void GetMemory(tpMLProblem*);

  virtual void Copy(void*);
  virtual tpChar* TypeName()const;
};
//************************************************************************************************
tpBAPBBMOneDim::tpBAPBBMOneDim()
{
	  MaxProfitValueFlag;
	 tpBool MinInputsValueFlag;

};
//************************************************************************************************
tpBAPBBMOneDim::tpBAPBBMOneDim(const tpBAPBBMOneDim& x)
{
	*this=x;
};
//************************************************************************************************
tpBAPBBMOneDim::~tpBAPBBMOneDim()
{
};
//************************************************************************************************
void tpBAPBBMOneDim::operator = (const tpBAPBBMOneDim& x)
{
    tpBBM::operator = (x);
};
//************************************************************************************************
  void tpBAPBBMOneDim::Solve(void*,...)
  {
    void** x= &x_;
    tpSolver* p = (tpSolver*)(x[0]);
    tpGA* ga = (tpGA*)(x[1]);
    tpReal temp;

  if (ptIterationNumber != 0 && modf((solver->IterationNumber()*1.0)/(ptIterationNumber*1.0),&temp)==0)
  {

    tpIndex num;
    tpBool flag;

    for(tpIndex i=0;i<ptSize;i++)
    {
        num=rand()%ptSize;
        while(1)
        {
                flag=false;
                for(tpIndex j=0;j<i;j++)
                        if(ptOrder[j]==num)flag=true;
                                if(flag)
                                {
                                        num++;
                                        if(num==ptSize)num=0;
                                }
                                else
                                {
                                        ptOrder[i]=num;
                                        break;
                                }
        }

    }

	ptCurrentChild=(tpBAPSolution*)(solver->Children->GetIndivid(0));
    for(tpIndex i=0;i<ptSize;i++)
    {
		ptCurrentBufferIndex=ptOrder[i];

	    ptIterationNumber=0;

		tpInt  OldTime, NewTime;
		OldTime=clock();
		do
		{
                ptIterationNumber++;
                Iteration(p);
		}while(Termination(p)==false);
		NewTime=clock();
    }

	ptCurrentChild=(tpBAPSolution*)(solver->Children->GetIndivid(1));
    for(tpIndex i=0;i<ptSize;i++)
    {
		ptCurrentBufferIndex=ptOrder[0];
		ptCurrentIndexSet=0;

        UpBound=problem->FMachineLine.Buffer[num+1].Volume;
        LowBound=0;


		ptMaxBufferSize[ptCurrentBufferIndex]=;
		ptMinBufferSize[ptCurrentBufferIndex]=0;


	    ptIterationNumber=0;

		tpInt  OldTime, NewTime;
		OldTime=clock();
		do
		{
                ptIterationNumber++;
                Iteration(p);
		}while(Termination(p)==false);
		NewTime=clock();
    }

  }
  };
//************************************************************************************************
void tpBAPBBMOneDim::GetMaxProfitValue(tpMLProblem* x)
{
	tpReal temp;
	ptCurrentChild->BufferSize[ptCurrentBufferIndex]=ptMaxBufferSize[ptCurrentIndexSet];
	x->Solve(ptCurrentChild->BufferSize,&ptMaxProfitValue[ptCurrentIndexSet],&temp);
};
//************************************************************************************************
void tpBAPBBMOneDim::GetMinInputsValue(tpMLProblem* x)
{
	tpReal temp;
	ptCurrentChild->BufferSize[ptCurrentBufferIndex]=ptMinBufferSize[ptCurrentIndexSet];
	x->Solve(ptCurrentChild->BufferSize,&temp,&ptMinInputsValue[ptCurrentIndexSet]);
};
//************************************************************************************************
  void tpBAPBBMOneDim::Branching(tpSolver* x)
  {
	  MLProblem* problem = (MLProblem*)(x);
	  tpInt Difference=0;
	  tpInt HalfDifference=0;
	  if(ptCurrentIteration==1)
	  {
		ptCurrentIndexSet=0;
		ptMaxIndexSet=0;
		ptMaxBufferSize[ptCurrentIndexSet]=problem->FMachineLine.Buffer[ptCurrentBufferIndex+1].Volume;
		ptMinBufferSize[ptCurrentIndexSet]=0;
	  }
	  else
	  {
		ptMaxIndexSet++;
        Difference=ptMaxBufferSize[ptCurrentIndexSet]-ptMinBufferSize[ptCurrentIndexSet];
        HalfDifference=floor(Difference*1.0/2);
		ptMaxBufferSize[ptMaxIndexSet]=ptMaxBufferSize[ptCurrentIndexSet];
		ptMinBufferSize[ptMaxIndexSet]=ptMinBufferSize[ptCurrentIndexSet]+HalfDifference+1;
        ptMaxBufferSize[ptMaxIndexSet]=ptMinBufferSize[ptCurrentIndexSet]+HalfDifference;
	  }
  };
//************************************************************************************************
  void tpBAPBBMOneDim::Bounding(tpSolver* x)
  {
      tpReal temp;

	  if(ptCurrentIteration==1)
	  {
        ptCurrentChild->BufferSize[ptCurrentBufferIndex]=ptMaxBufferSize[ptCurrentIndexSet];
        x->Solve(ptCurrentChild->BufferSize,&ptMaxProfitValue[ptCurrentIndexSet],&temp);

        ptCurrentChild->BufferSize[ptCurrentBufferIndex]=ptMinBufferSize[ptCurrentIndexSet];
        x->Solve(ptCurrentChild->BufferSize,&temp,&ptMinInputsValue[ptCurrentIndexSet]);
	  }
	  else
	  {
        ptCurrentChild->BufferSize[ptCurrentBufferIndex]=ptMaxBufferSize[ptCurrentIndexSet];
        x->Solve(ptCurrentChild->BufferSize,&ptMaxProfitValue[ptCurrentIndexSet],&temp);
        ptMinBufferSize[ptMaxIndexSet]=ptMaxProfitValue[ptCurrentIndexSet];

        ptCurrentIndexSet=0;
        for(tpIndex i=1;i<=ptMaxIndexSet;i++)
            if((ptMaxProfitValue[ptCurrentIndexSet]-ptMinInputsValue[ptCurrentIndexSet])<(ptMaxProfitValue[i]-ptMinInputsValue[i]))
                ptCurrentIndexSet=i;
	  }
  };
//************************************************************************************************
  tpBool tpBAPBBMOneDim::NotBranched(tpSolver* x);
  {
      if(ptMaxBufferSize[ptCurrentIndexSet]==tMinBufferSize[ptCurrentIndexSet])return true;
      else return false;
  };
//************************************************************************************************
void tpBAPBBMOneDim::GetMemory(tpMLProblem* p)
{
	ptSize=p->GetSize();

    if(ptOrder)delete[] ptOrder;
    ptOrder= new tpIndex[ptSize];

    if(ptMaxProfitValue)delete[] ptMaxProfitValue;
    ptMaxProfitValue= new tpIndex[ptUpBound+1];

    if(ptMinInputsvalue)delete[] ptMinInputsvalue;
    ptMinProfitValue= new tpIndex[ptUpBound+1];

    if(ptMaxBufferSize)delete[] ptMaxBufferSize;
    ptMaxBufferSize= new tpIndex[ptUpBound+1];

    if(ptMinBufferSize)delete[] ptMinBufferSize;
    ptMinBufferSize= new tpIndex[ptUpBound+1];
};
//************************************************************************************************
 void tpBAPBBMOneDim::Copy(void* x)
 {
    tpBAPBBMOneDim* y = (tpBAPBBMOneDim*)(x);
    *this = *y;
 };
//************************************************************************************************
tpChar* tpBAPBBMOneDim::TypeName()const
{
	return "BAPBBMOneDim";
};
//************************************************************************************************
#endif
