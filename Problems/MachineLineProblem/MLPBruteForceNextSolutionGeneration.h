#ifndef hpp_MLPBruteForceNextSolutionGeneration_hpp
#define hpp_MLPBruteForceNextSolutionGeneration_hpp

#include "..\..\Interface\ISolver.h"
#include "MLPSolution.h"
#include "MLProblem.h"

class MLPBruteForceNextSolutionGeneration:public ISolver
{
 public:
  MLPBruteForceNextSolutionGeneration();
  MLPBruteForceNextSolutionGeneration(const MLPBruteForceNextSolutionGeneration&);
  void operator = (const MLPBruteForceNextSolutionGeneration&);
  virtual ~MLPBruteForceNextSolutionGeneration();

  virtual SolverResult eSolve(void*, ...);

  //virtual void Copy(const void*);
  //virtual string TypeName()const;
  //virtual void FreeAllMemory();
  //virtual BaseObject* pClone()const;
};
#endif
