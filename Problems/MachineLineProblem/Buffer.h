#ifndef HPP_BUFFER_HPP
#define HPP_BUFFER_HPP
#include <ctype.h>
class Buffer
{
 protected:
  int _MQuantity;
  int* _PutingDetailMachineNumber;
  int* _TakingDetailMachineNumber;
 public:
  int PutingDetailMachineQuantity;
  int TakingDetailMachineQuantity;

  int Number;
  long Volume;

  Buffer();
  Buffer(const Buffer&);
  void operator = (const Buffer&);
  virtual ~Buffer();

  void GetMemory();
  void GetMemory(int);
  void FreeMemory();

  int& PutingDetailMachineNumber(int);
  int& TakingDetailMachineNumber(int);

  int AddPutingDetailMachine(int);
  int AddTakingDetailMachine(int);

  int MachineQuantity() const;
  void SetMachineQuantity(int);

  //virtual void Remove();
  //virtual void Copy(const void*);
  //virtual void* Clone()const;
};
#endif
