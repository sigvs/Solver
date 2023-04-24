#include "WorkStation.h"
//************************************************************************************************
  WorkStation::WorkStation()
  {
	Number=-1;
   MachineNumber=0;

	HelpMachine.Lambda=0;
	HelpMachine.Mu=0;
	HelpMachine.C=0;

	GivingDetailBufferListNumber=-1;
	TakingDetailBufferListNumber=-1;

	GivingDetailBufferNumber=-1;
	TakingDetailBufferNumber=-1;
  };
//************************************************************************************************
  WorkStation::WorkStation(const WorkStation& x)
  {
	Number=-1;
        MachineNumber=0;

	HelpMachine.Lambda=0;
	HelpMachine.Mu=0;
	HelpMachine.C=0;

	GivingDetailBufferListNumber=-1;
	TakingDetailBufferListNumber=-1;

	GivingDetailBufferNumber=-1;
	TakingDetailBufferNumber=-1;
        *this=x;
  };
//************************************************************************************************
  void WorkStation::operator = (const WorkStation& x)
  {
        Machine::operator = (x);

	Number=x.Number;
        MachineNumber=x.MachineNumber;

	HelpMachine=x.HelpMachine;

	GivingDetailBufferListNumber=x.GivingDetailBufferListNumber;
	TakingDetailBufferListNumber=x.TakingDetailBufferListNumber;

	GivingDetailBufferNumber=x.GivingDetailBufferNumber;
	TakingDetailBufferNumber=x.TakingDetailBufferNumber;
  };
//************************************************************************************************
  bool WorkStation::operator == (const WorkStation& x)const
  {
     if(!(Machine::operator == (x)))
	 {
	   if(MachineNumber!=x.MachineNumber)return false;
	   if(MaxMachineNumber!=x.MaxMachineNumber)return false;
       if(MinMachineNumber!=x.MinMachineNumber)return false;
	   return true;
	 }
	 else return false;
  };
//************************************************************************************************
  bool WorkStation::operator != (const WorkStation& x)const
  {
    return !(this->operator == (x));
  };
//************************************************************************************************
  WorkStation::~WorkStation()
  {
  };
 //************************************************************************************************
  void WorkStation::FreeMemory()
  {
        HelpMachine.Remove();
  };
// //************************************************************************************************
//  void WorkStation::Remove()
//  {
//      FreeMemory();
//      Machine::Remove();
//  };
// //************************************************************************************************
// void WorkStation::Copy(void* x)
// {
//    WorkStation* y = (WorkStation*)(x);
//    *this = *y;
// };
////************************************************************************************************
//void* WorkStation::Clone()const
//{
//	WorkStation* p = new WorkStation(*this);
//	return p;
//};
////************************************************************************************************
//
