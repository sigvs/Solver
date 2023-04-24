#ifndef hpp_GA_hpp
#define hpp_GA_hpp

#include "..\Evolutional\EvolutionalAlgorithm.h"

class GA:public EvolutionalAlgorithm
{
 public:
  ISolver* pCrossover;

  GA();
  GA(const GA&);
  void operator = (const GA&);
  virtual ~GA();

  virtual void Iteration(void* x_, ...) override;

};
#endif
