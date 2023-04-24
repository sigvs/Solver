#ifndef hpp_OnePointCrossover_hpp
#define hpp_OnePointCrossover_hpp

#include "..\Evolutional\Population.h"
#include "..\..\Interface\ISolver.h"
#include "..\..\Interface\IArray.h"
#include "..\Evolutional\EvolutionalAlgorithm.h"

template <typename T>
class OnePointCrossover:public ISolver
{
 protected:
  double ptCrossoverProbability;
 public:
  OnePointCrossover();
  OnePointCrossover(const OnePointCrossover&);
  void operator = (const OnePointCrossover&);
  virtual ~OnePointCrossover();

  SolverResult eSolve(void*, ...);

  double CrossoverProbability()const;
  void SetCrossoverProbability(double);

};
#endif