#ifndef hpp_EvolutionalAlgorithm_hpp
#define hpp_EvolutionalAlgorithm_hpp


#include "..\Common\IterationSolver.h"
#include "Population.h"
#include "..\..\Interface\IRemoveable.h"

class EvolutionalAlgorithm:public IterationSolver
{
 public:
  Population* pParents;
  Population* pChildren;
  ISolver* pSelection;
  ISolver* pMutation;
  ISolver* pAdder;
  ISolver* pTerminator;

  EvolutionalAlgorithm();
  EvolutionalAlgorithm(const EvolutionalAlgorithm&);
  void operator = (const EvolutionalAlgorithm&);
  virtual ~EvolutionalAlgorithm();

  virtual bool bTerminate (void*,...);
  virtual SolverResult eSolve(void*,...) override;
  virtual void Iteration(void*,...) override;

  void ViewCurrentState(void*, ...) override;

};
#endif
