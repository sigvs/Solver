#ifndef HPP_MACHINE_HPP
#define HPP_MACHINE_HPP

#include "..\..\Interface\IRemoveable.h"

class Machine
{
 public:
  double Lambda;
  double Mu;
  double C;

  Machine();
  Machine(const Machine&);
  void operator = (const Machine&);
  virtual ~Machine();

  bool operator == (const Machine&)const;
  bool operator != (const Machine&)const;

  virtual void Remove();
};

#endif
