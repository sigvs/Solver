#ifndef HPP_WorkStation_HPP
#define HPP_WorkStation_HPP

#include "Machine.h"

class WorkStation:public Machine
{
 public:
  int Number;
  int MachineNumber;
  int MaxMachineNumber;
  int MinMachineNumber;


  Machine HelpMachine;

  int GivingDetailBufferListNumber;
  int TakingDetailBufferListNumber;

  int GivingDetailBufferNumber;
  int TakingDetailBufferNumber;

  WorkStation();
  WorkStation(const WorkStation&);
  void operator = (const WorkStation&);
  virtual ~WorkStation();


  bool operator == (const WorkStation&)const;
  bool operator != (const WorkStation&)const;

  void FreeMemory();

  //virtual void Remove();
  //virtual void Copy(void*);
  //virtual void* Clone()const;
};
#endif
