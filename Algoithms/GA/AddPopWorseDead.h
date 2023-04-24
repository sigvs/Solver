#ifndef hpp_tAddPopWorseDead_hpp
#define hpp_tAddPopWorseDead_hpp

#include "..\Evolutional\Population.h"
#include "..\Common\Solution.h"
#include "GA.h"
#include <string>

class AddPopWorseDead:public ISolver
{
 public:
  AddPopWorseDead();
  AddPopWorseDead(const AddPopWorseDead&);
  void operator = (const AddPopWorseDead&);
  virtual ~AddPopWorseDead();

  virtual SolverResult eSolve(void*, ...);
  virtual void AddOne(ISolver*,GA*,Solution*);
};
#endif
