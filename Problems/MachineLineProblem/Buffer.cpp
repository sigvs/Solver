#include "Buffer.h"
//************************************************************************************************
Buffer::Buffer()
  {
   Number=0;
   Volume=0;

   _MQuantity=0;

   PutingDetailMachineQuantity=0;
   TakingDetailMachineQuantity=0;

   _PutingDetailMachineNumber=NULL;
   _TakingDetailMachineNumber=NULL;
  };
//************************************************************************************************
  Buffer::Buffer(const Buffer& x)
  {
   Number=0;
   Volume=0;

   _MQuantity=0;

   PutingDetailMachineQuantity=0;
   TakingDetailMachineQuantity=0;

   _PutingDetailMachineNumber=NULL;
   _TakingDetailMachineNumber=NULL;

   *this=x;
  };
//************************************************************************************************
  void Buffer::operator = (const Buffer& x)
  {
   if(_MQuantity!=x._MQuantity) GetMemory(x._MQuantity);

   Number=x.Number;
   Volume=x.Volume;

   PutingDetailMachineQuantity=x.PutingDetailMachineQuantity;
   TakingDetailMachineQuantity=x.TakingDetailMachineQuantity;

   for(int i=0;i<_MQuantity;i++)
   {
    _PutingDetailMachineNumber[i]=x._PutingDetailMachineNumber[i];
    _TakingDetailMachineNumber[i]=x._TakingDetailMachineNumber[i];
   }
  };
//************************************************************************************************
  Buffer::~Buffer()
  {
   FreeMemory();
  };
//************************************************************************************************
  void Buffer::GetMemory()
  {
   if(_MQuantity>0 && !_PutingDetailMachineNumber)_PutingDetailMachineNumber = new int[_MQuantity];
   if(_MQuantity>0 && !_TakingDetailMachineNumber)_TakingDetailMachineNumber = new int[_MQuantity];
  };
//************************************************************************************************
  void Buffer::GetMemory(int x)
  {
   _MQuantity=x;
   GetMemory();
  };
//************************************************************************************************
  void Buffer::FreeMemory()
  {
   if(_PutingDetailMachineNumber)delete[] _PutingDetailMachineNumber;
   if(_TakingDetailMachineNumber)delete[] _TakingDetailMachineNumber;

   Number=0;
   Volume=0;
   _MQuantity=0;

   PutingDetailMachineQuantity=0;
   TakingDetailMachineQuantity=0;

   _PutingDetailMachineNumber=NULL;
   _TakingDetailMachineNumber=NULL;
  };
//************************************************************************************************
  int& Buffer::PutingDetailMachineNumber(int x)
  {
      return _PutingDetailMachineNumber[x];
  };
//************************************************************************************************
  int& Buffer::TakingDetailMachineNumber(int x)
  {
      return _TakingDetailMachineNumber[x];
  };
  //************************************************************************************************
  int Buffer::AddPutingDetailMachine(int x)
  {
   _PutingDetailMachineNumber[PutingDetailMachineQuantity]=x;
   PutingDetailMachineQuantity++;
   return PutingDetailMachineQuantity-1;
  };
//************************************************************************************************
  int Buffer::AddTakingDetailMachine(int x)
  {
   _TakingDetailMachineNumber[TakingDetailMachineQuantity]=x;
   TakingDetailMachineQuantity++;
   return TakingDetailMachineQuantity-1;
  };
//************************************************************************************************
  int Buffer::MachineQuantity() const
  {
   return _MQuantity;
  };
//************************************************************************************************
  void Buffer::SetMachineQuantity(int x)
  {
   FreeMemory();
   GetMemory(x);
  };
////************************************************************************************************
//void Buffer::Remove()
//{
//	FreeMemory();
//};
////************************************************************************************************
//void Buffer::Copy(const void* x)
//{
//	Buffer* y = (Buffer*)(x);
//	*this = *y;
//};
////************************************************************************************************
//void* Buffer::Clone()const
//{
//	Buffer* p = new Buffer(*this);
//	return p;
//};
////************************************************************************************************

