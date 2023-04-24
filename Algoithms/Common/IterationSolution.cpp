#include "iterationsolution.h"
//************************************************************************************************
 IterationSolution::IterationSolution()
 {
     uIterationNumber=0;
 };
//************************************************************************************************
 IterationSolution::IterationSolution(const IterationSolution& x)
 {
     uIterationNumber=0;
     *this=x;
 };
//************************************************************************************************
 void IterationSolution::operator = (const IterationSolution& x)
 {
     Solution::operator = (x);
     uIterationNumber=x.uIterationNumber;
 };
//************************************************************************************************
 IterationSolution::~IterationSolution()
 {
     __FreeMemory();
 };
//************************************************************************************************
 void IterationSolution::__FreeMemory()
 {
     uIterationNumber=0;
 };
//************************************************************************************************
 void IterationSolution::Remove()
 {
     __FreeMemory();
 };
//************************************************************************************************
 void IterationSolution::Copy(const void* x)
 {
     IterationSolution* y = (IterationSolution*)(x);
     *this=*y;
 };
//************************************************************************************************
