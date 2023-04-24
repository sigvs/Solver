#ifndef hpp_tBAPOnePointCrossover_hpp
#define hpp_tBAPOnePointCrossover_hpp

#include "Solver.hpp"
#include "BAPSolution.hpp"

class tpBAPOnePointCrossover:public tpSolver
{
 protected:
  tpReal ptCrossoverProbability;
 public:
  tpBAPOnePointCrossover();
  tpBAPOnePointCrossover(const tpBAPOnePointCrossover&);
  void operator = (const tpBAPOnePointCrossover&);
  virtual ~tpBAPOnePointCrossover();

  virtual void Solve(void*, ...);

  tpReal CrossoverProbability()const;
  void SetCrossoverProbability(tpReal);

  virtual void Copy(void*);
  virtual tpChar* TypeName()const;
};
//************************************************************************************************
tpBAPOnePointCrossover::tpBAPOnePointCrossover()
{
};
//************************************************************************************************
tpBAPOnePointCrossover::tpBAPOnePointCrossover(const tpBAPOnePointCrossover& x)
{
	*this=x;
};
//************************************************************************************************
tpBAPOnePointCrossover::~tpBAPOnePointCrossover()
{
};
//************************************************************************************************
void tpBAPOnePointCrossover::operator = (const tpBAPOnePointCrossover& x)
{
	tpSolver::operator = (x);
	ptCrossoverProbability=x.ptCrossoverProbability;
};
//************************************************************************************************
void tpBAPOnePointCrossover::Solve(void* x_, ...)
 {
    void** x= &x_;
    tpMLProblem* problem = (tpMLProblem*)(x[0]);
    tpGA* solver = (tpGA*)(x[1]);
    tpReal CrossoverProbability = rand()*1.0/(RAND_MAX*1.0);
    if(CrossoverProbability <= ptCrossoverProbability)
    {
        tpBAPSolution* FirstChild =(tpBAPSolution*)(solver->Children->GetIndivid(0));
        tpBAPSolution* SecondChild =(tpBAPSolution*)(solver->Children->GetIndivid(1));

        tpIndex mixNumber=rand()%FirstChild->GetBufferNumber();
        tpInt h;

        for(tpIndex i=0;i<mixNumber;i++)
        {
            h=FirstChild->BufferSize(i);
            FirstChild->BufferSize(i)=SecondChild->BufferSize(i);
            SecondChild->BufferSize(i)=h;
        }

        solver->Children->GetIndivid(0)->SetValue(problem);
        solver->Children->GetIndivid(1)->SetValue(problem);
    }
 };
 //************************************************************************************************
tpReal tpBAPOnePointCrossover::CrossoverProbability()const
{
    return ptCrossoverProbability;
};
//************************************************************************************************
void tpBAPOnePointCrossover::SetCrossoverProbability(tpReal x)
{
    ptCrossoverProbability=x;
};
//************************************************************************************************
void tpBAPOnePointCrossover::Copy(void* x)
 {
    tpBAPOnePointCrossover* y = (tpBAPOnePointCrossover*)(x);
    *this = *y;
 };
//************************************************************************************************
tpChar* tpBAPOnePointCrossover::TypeName()const
{
	return "BAPOnePointCrossover";
};
//************************************************************************************************
#endif
