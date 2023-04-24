#ifndef hpp_tIterationTerminator_hpp
#define hpp_tIterationTerminator_hpp

#include "..\..\Interface\ISolver.h"
#include "iterationsolver.h"

class IterationTerminator:public ISolver
{
 protected:
  int _iIterationNumber;
 public:
  IterationTerminator();
  IterationTerminator(const IterationTerminator&);
  void operator = (const IterationTerminator&);
  virtual ~IterationTerminator();

  virtual SolverResult eSolve(void*, ...);

  int iGetIterationNumber()const;
  void SetIterationNumber(int);
};
#endif
