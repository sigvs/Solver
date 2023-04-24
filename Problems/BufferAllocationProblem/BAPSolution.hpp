#ifndef hpp_BAPSolution_hpp
#define hpp_BAPSolution_hpp

#include "..\..\Algoithms\Common\IterationSolution.h"
using namespace std;

class BAPSolution:public IterationSolution, IArray<long>, IRemoveable
{
    protected:
        size_t ptBufferNumber;
        long* ptBufferSize;
	public:
        double Profit;
        double Inputs;

		BAPSolution();
		BAPSolution(const BAPSolution&);
		void operator = (const BAPSolution&);
		virtual ~BAPSolution();

		void GetMemory();
		void FreeMemory();

		virtual void SetValue(ISolver*);
		virtual double Value()const;

		virtual void SetBufferNumber(size_t);
		virtual size_t GetBufferNumber()const;

        long& BufferSize(size_t);

        virtual bool bEqual(void*)const override;
        virtual bool bNotEqual(void*)const override;
        virtual bool bWorse(void*)const override;
        virtual bool bBetter(void*)const override;
        virtual bool bWorseOrEqual(void*)const override;
        virtual bool bBetterOrEqual(void*)const override;
        virtual bool bIdentical(void*)const override;
        virtual bool bNotIdentical(void*)const override;

        friend ofstream& operator <<(ofstream& , BAPSolution&);
//        friend ifstream& operator >>(ifstream& , tpMLProblem&);
        friend ostream& operator <<(ostream& , BAPSolution&);

        // Унаследовано через IRemoveable
        virtual void Remove() override;

        // Унаследовано через IArray
        virtual size_t GetElementCount() override;
        virtual long GetElement(size_t i) override;
        virtual void SetElement(size_t i, long v) override;
        // Унаследовано через ICloneable
        virtual void* Clone()const override;
        // Унаследовано через IGenerative
        virtual void Generate(void*, ...)override;
};
//************************************************************************************************/
BAPSolution::BAPSolution()
{
        ptBufferSize=NULL;
        Profit=0.0;
        Inputs=0.0;
        ptBufferNumber=0;
};
//************************************************************************************************/
BAPSolution::BAPSolution(const BAPSolution& x)
{
        ptBufferSize=NULL;
        Profit=0.0;
        Inputs=0.0;
        ptBufferNumber=0;
        *this = x;
};
//************************************************************************************************/
void BAPSolution::operator = (const BAPSolution& x)
{
    IterationSolution::operator = (x);
    if(ptBufferNumber!=x.ptBufferNumber)SetBufferNumber(x.ptBufferNumber);
    for(size_t i=0;i<ptBufferNumber;i++)
        ptBufferSize[i]=x.ptBufferSize[i];
    Profit=x.Profit;
    Inputs=x.Inputs;
};
//************************************************************************************************/
BAPSolution::~BAPSolution()
{
    FreeMemory();
};
//************************************************************************************************/
void BAPSolution::GetMemory()
{
	if(ptBufferSize)delete[] ptBufferSize;
	ptBufferSize=new long[ptBufferNumber];
};
//************************************************************************************************/
void BAPSolution::FreeMemory()
{
	if(ptBufferSize)delete[] ptBufferSize;
	ptBufferSize=NULL;
    Profit=0;
    Inputs=0;
    ptBufferNumber=0;
};
//************************************************************************************************/
void BAPSolution::SetBufferNumber(size_t s)
{
    ptBufferNumber=s;
    GetMemory();
};
//************************************************************************************************/
size_t BAPSolution::GetBufferNumber()const
{
    return ptBufferNumber;
};
//************************************************************************************************/
void BAPSolution::SetValue(ISolver* x)
{
	x->eSolve(ptBufferSize,&Profit,&Inputs);
};
//************************************************************************************************/
double BAPSolution::Value()const
{
	return Profit-Inputs;
};
//************************************************************************************************/
bool BAPSolution::bEqual (void* x)const
{
	BAPSolution* y = (BAPSolution*)(x);
	if(ptBufferNumber!=y->ptBufferNumber)return false;
	else
        if(Profit!=y->Profit)return false;
        else
            if(Inputs!=y->Inputs)return false;
            else
            {
                for(size_t i=0;i<ptBufferNumber;i++)
                    if(ptBufferSize[i]!=y->ptBufferSize[i])return false;
            }
	return true;
};
//************************************************************************************************/
long& BAPSolution::BufferSize(size_t i)
{
     if(i<ptBufferNumber)return ptBufferSize[i];
     else abort();
};
//************************************************************************************************/
bool BAPSolution::bNotEqual (void* x)const
{
	return !bEqual(x);
};
//************************************************************************************************/
bool BAPSolution::bWorse (void* x)const
{
	BAPSolution* y = (BAPSolution*)(x);
	return (Value()<y->Value());
};
//************************************************************************************************/
bool BAPSolution::bBetter (void* x)const
{
	BAPSolution* y = (BAPSolution*)(x);
	return (Value()>y->Value());
};
//************************************************************************************************/
bool BAPSolution::bBetterOrEqual (void* x)const
{
	BAPSolution* y = (BAPSolution*)(x);
	return (Value()>=y->Value());
};
//************************************************************************************************/
bool BAPSolution::bWorseOrEqual (void* x)const
{
	BAPSolution* y = (BAPSolution*)(x);
	return (Value()<=y->Value());

};
//************************************************************************************************/
void BAPSolution::Remove()
{
    FreeMemory();
};
//************************************************************************************************/
size_t BAPSolution::GetElementCount()
{
    return ptBufferNumber;
};

//************************************************************************************************/
long BAPSolution::GetElement(size_t i)
{
    return BufferSize(i);
};
//************************************************************************************************/
void BAPSolution::SetElement(size_t i, long v)
{
    BufferSize(i) = v;
};
//************************************************************************************************/
void BAPSolution::Generate(void* x, ...)
{
    BAPProblem* prb = (BAPProblem*)(x);
    for (size_t i = 0; i < ptBufferNumber; i++)
        ptBufferSize[i] = x.ptBufferSize[i];


}
//************************************************************************************************/
void* BAPSolution::Clone()const
{
    BAPSolution* tmp = new BAPSolution(this&);
}
//************************************************************************************************/
ofstream& operator <<(ofstream& out , BAPSolution& x)
{
   out<<"BufferNumber "<<x.ptBufferNumber<<" Value "<<x.Value()<<" Time "<<x.fSecond()<<" Profit "<<x.Profit<<" Inputs "<<x.Inputs<<endl;
   out<<"BufferSizes";
   for(size_t i=0;i<x.ptBufferNumber;i++)
      cout<<" "<<x.BufferSize(i);
   cout<<endl;
  return out;
}
ostream& operator <<(ostream& out , BAPSolution& x)
{
   out<<"BufferNumber "<<x.ptBufferNumber<<" Value "<<x.Value()<<" Time "<<x.fSecond() <<" Profit "<<x.Profit<<" Inputs "<<x.Inputs<<endl;
   out<<"BufferSizes ";
   for(size_t i=0;i<x.ptBufferNumber;i++)
      cout<<" "<<x.BufferSize(i);
   cout<<endl;
  return out;
}
//ifstream& operator >>(ifstream& , tpMLProblem&);
#endif
