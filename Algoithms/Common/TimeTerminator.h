#ifndef hpp_tTimeTerminator_hpp
#define hpp_tTimeTerminator_hpp

#include "..\..\Interface\ISolver.h"
#include "IterationSolver.h"

class TimeTerminator:public ISolver
{
 protected:
  float _fTime;
 public:
  TimeTerminator();
  TimeTerminator(const TimeTerminator&);
  void operator = (const TimeTerminator&);
  virtual ~TimeTerminator();

  virtual SolverResult eSolve(void*, ...);

  float fGetTime_sec()const;
  void SetTime_sec(float);

  //virtual void Remove();
  //virtual void Copy(const void*);
  //virtual void* Clone()const;
};
#endif
