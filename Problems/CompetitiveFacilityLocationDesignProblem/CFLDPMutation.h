#ifndef hpp_CFLDPMutation_hpp
#define hpp_CFLDPMutation_hpp

#include "..\..\Interface\ISolver.h"
#include "..\..\Algoithms\Evolutional\Population.h"
#include "..\..\Algoithms\Evolutional\EvolutionalAlgorithm.h"
#include "CFLDProblem.h"
#include "CFLDPSolution.h"
#include "CFLDPRandomOpenRandom.h"
#include "CFLDPDeviationDemandMutation.h"

class CFLDPMutation :public ISolver
{
private:
	CFLDPRandomOpenRandom* _VariantMutation;
	CFLDPDeviationDemandMutation* _DeviationMutation;
 public:
	 CFLDPMutation();
	 CFLDPMutation(const CFLDPMutation&);
  void operator = (const CFLDPMutation&);
  virtual ~CFLDPMutation();

  void SetVariantParametr(int p);
  void SetDeviationDemandMutationParametr(int p);

  virtual SolverResult eSolve(void*, ...);

};
#endif
