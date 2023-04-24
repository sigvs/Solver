#ifndef HPP_BAPMLPROBLEM_HPP
#define HPP_BAPMLPROBLEM_HPP

#include "MLProblem.hpp"
#include "MachineLine.hpp"
#include "Solver.hpp"
#include "PLineFunction.hpp"

//const tpReal eps = 1e-6;

class tpBAPMLProblem:public tpMLProblem
{
protected:
  tpSolver* ptRevenue;
  tpSolver* ptAlloc_cost;
 public:
  tpReal amort;

  tpBAPMLProblem();
  tpBAPMLProblem(const tpBAPMLProblem&);
  void operator = (const tpBAPMLProblem&);
  virtual ~tpBAPMLProblem();

  tpSolver* Revenue();
  void SetRevenue(tpSolver*);

  tpSolver* Alloc_cost();
  void SetAlloc_cost(tpSolver*);

  virtual void Solve(void*,...);
  void Solve(tpIndex,tpReal&,tpReal&);

  virtual void Copy(void*);
  virtual tpChar* TypeName()const;

  friend ofstream& operator <<(ofstream& , tpBAPMLProblem&);
  friend ifstream& operator >>(ifstream& , tpBAPMLProblem&);
  friend ostream& operator <<(ostream& , tpBAPMLProblem&);

};

//************************************************************************************************
 tpBAPMLProblem::tpBAPMLProblem()
 {
   ptRevenue=NULL;
   ptAlloc_cost=NULL;
 };
//************************************************************************************************
 tpBAPMLProblem::tpBAPMLProblem(const tpBAPMLProblem& x)
 {
  *this=x;
 };
//************************************************************************************************
 void tpBAPMLProblem::operator = (const tpBAPMLProblem& x)
 {
   ptRevenue = x.ptRevenue;
   ptAlloc_cost = x.ptAlloc_cost;
   amort=x.amort;
 }
//************************************************************************************************
 tpBAPMLProblem::~tpBAPMLProblem()
 {
   FreeMemory();
 }
//************************************************************************************************
  tpSolver* tpBAPMLProblem::Revenue()
  {
      return ptRevenue;
  };
//************************************************************************************************
  void tpBAPMLProblem::SetRevenue(tpSolver* x)
  {
      ptRevenue=x;
  };
//************************************************************************************************
  tpSolver* tpBAPMLProblem::Alloc_cost()
  {
      return ptAlloc_cost;
  };
//************************************************************************************************
  void tpBAPMLProblem::SetAlloc_cost(tpSolver* x)
  {
      ptAlloc_cost=x;
  };
//************************************************************************************************
 void tpBAPMLProblem::Solve(void*x_,...)
 {

  void** hx= &x_;
  tpInt* x = (tpInt*)(hx[0]);
  tpReal* Profit = (tpReal*)(hx[1]);
  tpReal* Inputs = (tpReal*)(hx[2]);

  for(tpIndex i=0;i<GetSize();i++)
   FMachineLine.Buffer(i+1)->Volume=x[i];

  Solve(GetSize(),*Profit,*Inputs);
 };
//************************************************************************************************
 void tpBAPMLProblem::Solve(tpIndex s, tpReal& Profit,tpReal& Inputs)
 {
  tpReal sum=0;
  for(tpIndex i=0;i<s;i++)
   sum+=FMachineLine.Buffer(i+1)->Volume;

  tpMachine p;
  p.Lambda=1;
  p.Mu=1;
  p.C=1;
  tpReal avg_stock=1;
  ReduceLine(&p,avg_stock,inv_coef);

  FMachineLine=FRMachineLine;

  tpReal debit=p.C/(1+p.Lambda/p.Mu);
  tpReal yh=0;
  ptRevenue->Solve(&debit,&yh);
  yh*=amort;

  tpReal yh1=0;
  ptAlloc_cost->Solve(&sum,&yh1);
  yh1+=amort*avg_stock;

  Profit=yh;
  Inputs=yh1;
 };
//************************************************************************************************
 void tpBAPMLProblem::Copy(void* x)
 {
    tpBAPMLProblem* y = (tpBAPMLProblem*)(x);
    *this = *y;
 };

//************************************************************************************************
 ifstream & operator >>(ifstream& in , tpBAPMLProblem& x)
 {
  tpChar s[256];

  tpIndex np=0;
  while(true)
  {
		if(np==4)break;
		else if(in.eof()==true)abort();

        in>>s;


        if(strncmp(s,"MachineLineParameter",20)==0)
		{
         in>>x.FMachineLine;
         x.FRMachineLine=x.FMachineLine;
         np++;
         continue;
        }

		if(strncmp(s,"BufferDetailCosts",17)==0)
		{
         for(tpIndex i=0;i<x.BufferQuantity();i++)
          in>>x.det_cost[i];
         np++;
         continue;
		}

		if(strncmp(s,"AmortizationPeriod",18)==0)
		{
         in>>x.amort;
         np++;
         continue;
        }

        if(strncmp(s,"InventoryCostCoefficient",24)==0)
        {
	     in>>x.inv_coef;
	     np++;
         continue;
        }

  }
  return in;
 };
//************************************************************************************************
 ofstream & operator <<(ofstream & out , tpBAPMLProblem & x)
 {
   out<<"MachineLineParameter"<<endl<<x.FMachineLine<<endl;
   out<<"BufferDetailCosts"<<endl;
   for(tpIndex i=0;i<x.BufferQuantity();i++) out<<x.det_cost[i]<<' ';
   out<<endl;
   out<<"AmortizationPeriod"<<endl<<x.amort<<endl;
   out<<"InventoryCostCoefficient"<<endl<<x.inv_coef<<endl;
  return out;
 };
//************************************************************************************************
 ostream & operator <<(ostream & out , tpBAPMLProblem & x)
 {
   out<<"MachineLineParameter"<<endl<<x.FMachineLine<<endl;
   out<<"BufferDetailCosts"<<endl;
   for(tpIndex i=0;i<x.BufferQuantity();i++) out<<x.det_cost[i]<<' ';
   out<<endl;
   out<<"AmortizationPeriod"<<endl<<x.amort<<endl;
   out<<"InventoryCostCoefficient"<<endl<<x.inv_coef<<endl;
  return out;
 };
//************************************************************************************************
#endif
