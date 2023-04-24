#ifndef HPP_MachineLine_HPP
#define HPP_MachineLine_HPP

#include <iostream>
#include <fstream>
#include "Buffer.h"
#include "WorkStation.h"
using namespace std;
class MachineLine
{
 protected:
  int _WQuantity;
  int _BQuantity;
  WorkStation* _WorkStation;
  Buffer* _Buffer;
  bool* _ConsideredWorkStation; //WorkStation that we use
  bool* _ConsideredBuffer; //buffer that we use
 public:
  int ConsideredWorkStationQuantity; //Considered WorkStation quantity
  int ConsideredBufferQuantity; //Considered buffer quantity

  MachineLine();
  MachineLine(const MachineLine&);
  void operator = (const MachineLine&);
  virtual ~MachineLine();

  void GetWorkStationMemory();
  void GetWorkStationMemory(int);
  void FreeWorkStationMemory();

  void GetBufferMemory();
  void GetBufferMemory(int);
  void FreeBufferMemory();

  void GetMemory(int,int);
  void FreeMemory();

  friend ofstream& operator <<(ofstream&, MachineLine&);
  friend ifstream& operator >>(ifstream&, MachineLine&);
  friend ostream& operator <<(ostream&, MachineLine&);

  int WorkStationQuantity() const;
  void SetWorkStationQuantity(int);

  void ChangeWorkStations(int,WorkStation*);
  WorkStation* getWorkStation(int);
  Buffer* getBuffer(int);

  bool& ConsideredWorkStation(int); //WorkStation that we use
  bool& ConsideredBuffer(int); //buffer that we use

  int BufferQuantity() const;
  void SetBufferQuantity(int);

  //virtual void Remove();
  //virtual void Copy(const void*);
  //virtual void* Clone()const;
};
#endif
