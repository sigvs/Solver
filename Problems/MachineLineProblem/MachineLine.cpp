#include "MachineLine.h"
#include <string>

//************************************************************************************************
MachineLine::MachineLine()
 {
  ConsideredWorkStationQuantity=0;
  ConsideredBufferQuantity=0;

  _WQuantity=0;
  _BQuantity=0;

  _WorkStation=NULL;
  _Buffer=NULL;

  _ConsideredWorkStation=NULL;
  _ConsideredBuffer=NULL;

 };
//************************************************************************************************
 MachineLine::MachineLine(const MachineLine& x)
 {
  ConsideredWorkStationQuantity=0;
  ConsideredBufferQuantity=0;

  _WQuantity=0;
  _BQuantity=0;

  _WorkStation=NULL;
  _Buffer=NULL;

  _ConsideredWorkStation=NULL;
  _ConsideredBuffer=NULL;

  *this=x;
 };
//************************************************************************************************
 void MachineLine::operator = (const MachineLine& x)
 {
  if(_WQuantity!=x._WQuantity)
  {
   FreeWorkStationMemory();
   GetWorkStationMemory(x._WQuantity);
  }

  for(int i=0;i<_WQuantity;i++)
  {
   _WorkStation[i]=x._WorkStation[i];
   _ConsideredWorkStation[i]=x._ConsideredWorkStation[i];
  }

  ConsideredWorkStationQuantity=x.ConsideredWorkStationQuantity;

  if(_BQuantity!=x._BQuantity)
  {
   FreeBufferMemory();
   GetBufferMemory(x._BQuantity);
  }

  for(int i=0;i<_BQuantity;i++)
  {
   _Buffer[i]=x._Buffer[i];
   _ConsideredBuffer[i]=x._ConsideredBuffer[i];
  }

  ConsideredBufferQuantity=x.ConsideredBufferQuantity;

 };
//************************************************************************************************
 MachineLine::~MachineLine()
 {
  FreeMemory();
 };
//************************************************************************************************
 void MachineLine::GetWorkStationMemory()
 {
  if(_WQuantity>0 && !_WorkStation)_WorkStation = new WorkStation[_WQuantity];
  if(_WQuantity>0 && !_ConsideredWorkStation)_ConsideredWorkStation = new bool[_WQuantity];
  for(int i=0;i<_WQuantity;i++)_ConsideredWorkStation[i]=true;
  for(int i=0;i<_BQuantity;i++)_Buffer[i].SetMachineQuantity(_WQuantity);
 };
//************************************************************************************************
 void MachineLine::GetWorkStationMemory(int x)
 {
  _WQuantity=x;
  GetWorkStationMemory();
 };
//************************************************************************************************
 void MachineLine::FreeWorkStationMemory()
 {
  if(_WorkStation)delete[] _WorkStation;
  if(_ConsideredWorkStation)delete[] _ConsideredWorkStation;
  ConsideredWorkStationQuantity=0;
  _WQuantity=0;
  _WorkStation=NULL;
  _ConsideredWorkStation=NULL;
 };
//************************************************************************************************
 void MachineLine::GetBufferMemory()
 {
  if(_BQuantity>0 && !_Buffer)
	  _Buffer = new Buffer[_BQuantity];
  if(_BQuantity>0 && !_ConsideredBuffer)
	  _ConsideredBuffer = new bool[_BQuantity];
  for(int i=0;i<_BQuantity;i++)
	  ConsideredBuffer(i)=true;
 };
//************************************************************************************************
 void MachineLine::GetBufferMemory(int x)
 {
  _BQuantity=x;
  GetBufferMemory();
 };
//************************************************************************************************
 void MachineLine::FreeBufferMemory()
 {
  if(_Buffer)
	  delete[] _Buffer;
  if(_ConsideredBuffer)
	  delete[] _ConsideredBuffer;
  ConsideredBufferQuantity=0;
  _BQuantity=0;
  _Buffer=NULL;
  _ConsideredBuffer=NULL;
 };
//************************************************************************************************
 void MachineLine::GetMemory(int m,int b)
 {
  GetWorkStationMemory(m);
  GetBufferMemory(b);
 };
//************************************************************************************************
 void MachineLine::FreeMemory()
 {
  FreeWorkStationMemory();
  FreeBufferMemory();
 };
//************************************************************************************************
 int MachineLine::WorkStationQuantity() const
 {
  return _WQuantity;
 };
//************************************************************************************************
 void MachineLine::SetWorkStationQuantity(int m)
 {
  FreeWorkStationMemory();
  GetWorkStationMemory(m);
 };
//************************************************************************************************
 void MachineLine::ChangeWorkStations(int n, WorkStation* x)
 {
  if(_WQuantity!=n)
  {
   FreeWorkStationMemory();
   GetWorkStationMemory(n);
  }

  for(int i=0;i<_WQuantity;i++)
  {
   _WorkStation[i]=x[i];
   _ConsideredWorkStation[i]=true;
  }

  ConsideredWorkStationQuantity=n;

 };
//************************************************************************************************
  WorkStation* MachineLine::getWorkStation(int i)
  {
     if(i<_WQuantity)return &_WorkStation[i];
     else return NULL;
  };
//************************************************************************************************
  Buffer* MachineLine::getBuffer(int i)
  {
     if(i<_BQuantity)return &_Buffer[i];
     else return NULL;
  };
//************************************************************************************************
  bool& MachineLine::ConsideredWorkStation(int i)
  {
     if(i<_WQuantity)return _ConsideredWorkStation[i];
     else abort();
  };
//************************************************************************************************
  bool& MachineLine::ConsideredBuffer(int i)
  {
     if(i<_BQuantity)return _ConsideredBuffer[i];
     else abort();
  };
//************************************************************************************************
 int MachineLine::BufferQuantity() const
 {
  return _BQuantity;
 };
//************************************************************************************************
 void MachineLine::SetBufferQuantity(int b)
 {
  FreeBufferMemory();
  GetBufferMemory(b);
 };
//************************************************************************************************
 ifstream & operator >>(ifstream & in , MachineLine & x)
 {
  string s;
  char s1;
  int index,num1,num2,num3;
  double Lambda=0;
  double Mu=0;
  double C=0;
  long Volume;
  int np=0;
  while(true)
  {
		if(np==2)break;
		else if(in.eof()==true)abort();

        getline(in,s);

        if(s.find("BufferNumber")!=string::npos)
        {
            in>>num1;
            x.SetBufferQuantity(num1);
            np++;
            continue;
        }

        if(s.find("WorkStationNumber")!=string::npos)
        {
            in>>num2;
            x.SetWorkStationQuantity(num2);
            np++;
            continue;
        }
  }
  np=0;
  while(true)
  {
		if(np==2)break;
		else if(in.eof()==true)abort();

        getline(in,s);

        if(s.find("BufferVolume")!=string::npos)
        {
            for(int i=0;i<x.BufferQuantity();i++)
            {
                in>>index>>s1>>Volume;
                index--;
//                x.Buffer(index)->SetMachineQuantity(x.WorkStationQuantity());
                x.getBuffer(index)->Volume=Volume;
            }
            x.ConsideredBufferQuantity=x.BufferQuantity();

            np++;
            continue;
        }

        if(s.find("WorkStationParameter")!=string::npos)
        {
            for(int i=0;i<x.WorkStationQuantity();i++)
            {
                //in>>index>>s1>>Lambda>>Mu>>C>>num1>>num2>>num3;
                in>>index;
                in>>s1;
                in>>Lambda;
                in>>Mu;
                in>>C;
                in>>num1;
                in>>num2;
                in>>num3;
                index--;
                x.getWorkStation(index)->Number=index;
                x.getWorkStation(index)->Lambda=1/Lambda;
                x.getWorkStation(index)->Mu=1/Mu;
                x.getWorkStation(index)->C=1/C;
                x.getWorkStation(index)->GivingDetailBufferNumber=num1-1;
                x.getWorkStation(index)->GivingDetailBufferListNumber=x.getBuffer(num1-1)->AddTakingDetailMachine(index);
                x.getWorkStation(index)->TakingDetailBufferNumber=num2-1;
                x.getWorkStation(index)->TakingDetailBufferListNumber=x.getBuffer(num2-1)->AddPutingDetailMachine(index);
                x.getWorkStation(index)->MachineNumber=num3;
            }
            x.ConsideredWorkStationQuantity=x.WorkStationQuantity();
            np++;
            continue;
        }
  }
  return in;
};
//************************************************************************************************
 ostream& operator <<(ostream & out , MachineLine & x)
 {
  out<<"BufferNumber"<<endl<<x.BufferQuantity()<<endl;
  out<<"WorkStationNumber"<<endl<<x.WorkStationQuantity()<<endl;
  out<<"BufferVolume"<<endl;
  for(int i=0;i<x.BufferQuantity();i++)
   out<<(i+1)<<":"<<x.getBuffer(i)->Volume<<endl;
  out<<"WorkStationParameter"<<endl;
  for(int i=0;i<x.WorkStationQuantity();i++)
   out<<(i+1)<<":"<<1/x.getWorkStation(i)->Lambda<<" "<<1/x.getWorkStation(i)->Mu<<" "<<1/x.getWorkStation(i)->C<<" "<<(x.getWorkStation(i)->GivingDetailBufferNumber+1)<<" "<<(x.getWorkStation(i)->TakingDetailBufferNumber+1)<<" "<<x.getWorkStation(i)->MachineNumber<<endl;
  return out;
};
//************************************************************************************************
 ofstream& operator <<(ofstream & out , MachineLine & x)
 {
  out<<"BufferNumber"<<endl<<x.BufferQuantity()<<endl;
  out<<"WorkStationNumber"<<endl<<x.WorkStationQuantity()<<endl;
  out<<"BufferVolume"<<endl;
  for(int i=0;i<x.BufferQuantity();i++)
   out<<(i+1)<<":"<<x.getBuffer(i)->Volume<<endl;
  out<<"WorkStationParameter"<<endl;
  for(int i=0;i<x.WorkStationQuantity();i++)
	  out<<(i+1)<<":"<<1/x.getWorkStation(i)->Lambda<<" "<<1/x.getWorkStation(i)->Mu<<" "<<1/x.getWorkStation(i)->C<<" "<<(x.getWorkStation(i)->GivingDetailBufferNumber+1)<<" "<<(x.getWorkStation(i)->TakingDetailBufferNumber+1)<<" "<<x.getWorkStation(i)->MachineNumber<<endl;
  return out;
};
