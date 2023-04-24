#ifndef hpp_NSGA2PopulationAdder_hpp
#define hpp_NSGA2PopulationAdder_hpp

#include "..\..\Interface\ISolver.h"
#include "NSGA2Population.h"
#include "..\GA\GA.h"

class NSGA2PopulationAdder:public ISolver
{
 public:
  NSGA2PopulationAdder();
  NSGA2PopulationAdder(const NSGA2PopulationAdder&);
  void operator = (const NSGA2PopulationAdder&);
  virtual ~NSGA2PopulationAdder();

  virtual SolverResult eSolve(void*, ...);

};
#endif
