#ifndef hpp_RandomSelection_hpp
#define hpp_RandomSelection_hpp

#include "EvolutionalAlgorithm.h"
#include "..\Common\Solution.h"
#include "..\..\Interface\ISolver.h"


class RandomSelection:public ISolver
{
 public:
  RandomSelection();
  RandomSelection(const RandomSelection&);
  void operator = (const RandomSelection&);
  virtual ~RandomSelection();

  virtual SolverResult eSolve(void*, ...);

  //virtual void Remove();
  //virtual void Copy(const void*);
  //virtual void* Clone()const;
};
#endif
