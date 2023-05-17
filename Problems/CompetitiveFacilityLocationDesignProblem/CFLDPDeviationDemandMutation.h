#ifndef hpp_CFLDPDeviationDemandMutation_hpp
#define hpp_CFLDPDeviationDemandMutation_hpp

#include "..\..\Interface\ISolver.h"
#include "..\..\Algoithms\Evolutional\Population.h"
#include "..\..\Algoithms\Evolutional\EvolutionalAlgorithm.h"
#include "CFLDProblem.h"
#include "CFLDPSolution.h"

class CFLDPDeviationDemandMutation :public ISolver
{
 protected:
  int _k;
  int uniform(int a, int b);
  double uniform();
 public:
	 CFLDPDeviationDemandMutation();
	 CFLDPDeviationDemandMutation(const CFLDPDeviationDemandMutation&);
  void operator = (const CFLDPDeviationDemandMutation&);
  virtual ~CFLDPDeviationDemandMutation();

  void SetDeviationDemandMutationParametr(int p);

  virtual SolverResult eSolve(void*, ...);

};
#endif
