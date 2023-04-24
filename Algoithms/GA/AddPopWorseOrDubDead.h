#ifndef hpp_tAddPopWorseOrDubDead_hpp
#define hpp_tAddPopWorseOrDubDead_hpp

#include "..\Evolutional\Population.h"
#include "..\Common\Solution.h"
#include "..\..\Interface\ISolver.h"
#include "GA.h"
#include <string>

class AddPopWorseOrDubDead:public ISolver
{
 public:
  AddPopWorseOrDubDead();
  AddPopWorseOrDubDead(const AddPopWorseOrDubDead&);
  void operator = (const AddPopWorseOrDubDead&);
  virtual ~AddPopWorseOrDubDead();

  virtual SolverResult eSolve(void*, ...);
  virtual void AddOne(ISolver*, GA*, Solution*);

};
#endif
