#ifndef HPP_MLPROBLEM_HPP
#define HPP_MLPROBLEM_HPP

#include "..\..\Interface\ISolver.h"
#include "MachineLine.h"
#include <fstream>
using namespace std;

const double eps = 1e-6;

class MLProblem:public ISolver
{
protected:
  double w;

  double lam1;
  double mu1;
  double deb1;

  double lam2;
  double mu2;
  double deb2;

  double h;
  double avg_stock;

  double f11x0, f11xh;
  double f10x0, f10xh;
  double f01x0, f01xh;
  double f00x0, f00xh;

  double F11x0, F11xh;
  double F10x0, F10xh;
  double F01x0, F01xh;
  double F00x0, F00xh;

  double P11x0;
  double P11xh;
  double P10xh;
  double P01x0;

  double I1, I2;

  double A;
  double B;
  double E;
  double D;
  double di;
  double a1;
  double a2;

  void Parallel(Machine*,Machine*);
  void Series(Machine*,Machine*,double&,double&);
  void ReduceLine(Machine*,double&,double&);
  int R1();

  double ex(double);
  double fi(double);
  void func0(double&);
  void func1(double&,double&);
  void func2(double&);

  double fufm01(double);
  double fufm10(double);
  double loif01(double);
  double loif10(double);

  long _MaxBufferSumm;
 public:
  MachineLine FRMachineLine;
  MachineLine FMachineLine;

  double* det_cost;
  double inv_coef;

  MLProblem();
  MLProblem(const MLProblem&);
  void operator = (const MLProblem&);
  virtual ~MLProblem();

  void FreeMemory();

  int MachineQuantity() const;
  void SetMachineQuantity(int);

  int BufferQuantity() const;
  void SetBufferQuantity(int);

  int GetSize() const;

  SolverResult eSolve(void*,...) override;
  void GetParameterFromReduceLine(int,double&,double&);

  long MaxBufferSumm();

  virtual void Copy(const void*);
  virtual void Remove();
  virtual void* Clone()const;

  friend ofstream& operator <<(ofstream& , MLProblem&);
  friend ifstream& operator >>(ifstream& , MLProblem&);
  friend ostream& operator <<(ostream& , MLProblem&);

};
#endif

