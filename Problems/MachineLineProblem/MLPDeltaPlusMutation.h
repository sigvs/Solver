#ifndef hpp_MLPDeltaPlusMutation_hpp
#define hpp_MLPDeltaPlusMutation_hpp

#include "..\..\Interface\ISolver.h"
#include "..\..\Algoithms\Evolutional\Population.h"
#include "..\..\Algoithms\Evolutional\EvolutionalAlgorithm.h"
#include "MLProblem.h"
#include "MLPSolution.h"

class MLPDeltaPlusMutation:public ISolver
{
 protected:
  long ptDeltaMutation;
 public:
  MLPDeltaPlusMutation();
  MLPDeltaPlusMutation(const MLPDeltaPlusMutation&);
  void operator = (const MLPDeltaPlusMutation&);
  virtual ~MLPDeltaPlusMutation();

  virtual SolverResult eSolve(void*, ...);

  long DeltaMutation()const;
  void SetDeltaMutation(long);

};
#endif
