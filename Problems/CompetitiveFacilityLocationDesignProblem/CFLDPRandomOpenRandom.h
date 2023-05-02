#ifndef hpp_CFLDPRandomOpenRandom_hpp
#define hpp_CFLDPRandomOpenRandom_hpp

#include "..\..\Interface\ISolver.h"
#include "..\..\Algoithms\Evolutional\Population.h"
#include "..\..\Algoithms\Evolutional\EvolutionalAlgorithm.h"
#include "CFLDProblem.h"
#include "CFLDPSolution.h"

class CFLDPRandomOpenRandom :public ISolver
{
private:
	int	__open, __close, __dr;
 protected:
  int _S;
  int uniform(int a, int b);
  bool next(CFLDPSolution* s);
 public:
	 CFLDPRandomOpenRandom();
	 CFLDPRandomOpenRandom(const CFLDPRandomOpenRandom&);
  void operator = (const CFLDPRandomOpenRandom&);
  virtual ~CFLDPRandomOpenRandom();

  void SetS(int p);

  virtual SolverResult eSolve(void*, ...);

};
#endif
