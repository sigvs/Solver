#ifndef hpp_IncreasePopulationIfNotWorse_hpp
#define hpp_IncreasePopulationIfNotWorse_hpp

#include "..\..\Interface\ISolver.h"
#include "..\Evolutional\Population.h"
#include "..\Evolutional\EvolutionalAlgorithm.h"
class IncreasePopulationIfNotWorse :public ISolver
{
 public:
	 IncreasePopulationIfNotWorse();
	 IncreasePopulationIfNotWorse(const IncreasePopulationIfNotWorse&);
	 void operator = (const IncreasePopulationIfNotWorse&);
	 virtual ~IncreasePopulationIfNotWorse();

	virtual SolverResult eSolve(void*, ...) override;
	virtual void AddOne(ISolver* problem, Population* pop, Solution* Child);
};
#endif
