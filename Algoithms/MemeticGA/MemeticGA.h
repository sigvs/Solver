#ifndef hpp_MemeticGA_hpp
#define hpp_MemeticGA_hpp

#include "..\GA\GA.h"
#include <string>

class MemeticGA:public GA
{
 public:
  ISolver* pLocalOptimization;

  MemeticGA();
  MemeticGA(const MemeticGA&);
  void operator = (const MemeticGA&);
  virtual ~MemeticGA();

  virtual void Iteration(void* x_,...) override;

};
#endif
