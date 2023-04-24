#ifndef hpp_BAPPopulation_hpp
#define hpp_BAPPopulation_hpp

#include "..\..\Algoithms\Evolutional\Population.h"
#include "BAPSolution.hpp"

class BAPPopulation:public Population
{
    protected:
        size_t ptPopulationSize;
        size_t ptIndividSize;
        size_t ptMaxIndexIndivid;
        size_t ptMinIndexIndivid;
        BAPSolution* ptIndivid;
    public:
        BAPPopulation();
        BAPPopulation(const BAPPopulation&);
        void operator = (const BAPPopulation&);
        virtual ~BAPPopulation();

        void GetMemory();
        void FreeMemory();

        void GetIndividMemory();
        void FreeIndividMemory();

        virtual void SetIndividSize(size_t);
        virtual size_t GetIndividSize() const;

        virtual IterationSolution* GetIndivid(size_t);
        virtual BAPSolution* Individ(size_t);

        virtual void SetSize(size_t);

        virtual size_t MaxIndexIndivid()const;
        virtual size_t MinIndexIndivid()const;

        virtual size_t GetMaxIndexIndivid();
        virtual size_t GetMinIndexIndivid();

        virtual void FreeAllMemory();
};

//************************************************************************************************/
  BAPPopulation::BAPPopulation()
 {
    ptMaxIndexIndivid=0;
    ptMinIndexIndivid=0;
    ptIndividSize=0;
    ptPopulationSize=0;

    ptIndivid=NULL;
 };
//************************************************************************************************/
  BAPPopulation::BAPPopulation(const BAPPopulation& x)
 {
    ptMaxIndexIndivid=0;
    ptMinIndexIndivid=0;
    ptIndividSize=0;
    ptIndivid=NULL;
    ptPopulationSize=0;

    *this = x;
 };
//************************************************************************************************/
void  BAPPopulation::operator = (const BAPPopulation& x)
{
    Population::operator = (x);
    if(ptPopulationSize !=x.ptPopulationSize)SetSize(x.ptPopulationSize);
    ptPopulationSize = x.ptPopulationSize;
    if(ptIndividSize!=x.ptIndividSize)SetIndividSize(x.ptIndividSize);
    ptIndividSize = x.ptIndividSize;
    for(size_t i=0;i< ptPopulationSize;i++)
        ptIndivid[i]=x.ptIndivid[i];
    ptMaxIndexIndivid=x.ptMaxIndexIndivid;
    ptMinIndexIndivid=x.ptMinIndexIndivid;
};
//************************************************************************************************/
  BAPPopulation::~BAPPopulation()
 {
	 FreeMemory();
 };
//************************************************************************************************/
void BAPPopulation::GetMemory()
{
    if(ptIndivid)delete[] ptIndivid;
    ptIndivid=new BAPSolution[ptPopulationSize];
};
//************************************************************************************************/
void BAPPopulation::FreeMemory()
{
    if(ptIndivid)
    {
        FreeIndividMemory();
        delete[] ptIndivid;
    }
    ptIndivid=NULL;
    ptPopulationSize =0;
    ptIndividSize=0;
    ptMaxIndexIndivid=0;
    ptMinIndexIndivid=0;
};
//************************************************************************************************/
void BAPPopulation::GetIndividMemory()
{
    for(size_t i=0;i< ptPopulationSize;i++)
        ptIndivid[i].SetBufferNumber(ptIndividSize);
};
//************************************************************************************************/
void BAPPopulation::FreeIndividMemory()
{
    for(size_t i=0;i< ptPopulationSize;i++)
        ptIndivid[i].FreeMemory();
};
//************************************************************************************************/
void BAPPopulation::SetIndividSize(size_t x)
{
  ptIndividSize=x;
  GetIndividMemory();
};
//************************************************************************************************/
IterationSolution* BAPPopulation::GetIndivid(size_t i)
{
     if(i< ptPopulationSize)return &ptIndivid[i];
     else return NULL;
};
//************************************************************************************************/
size_t BAPPopulation::GetIndividSize()const
{
    return ptIndividSize;
};
//************************************************************************************************/
BAPSolution* BAPPopulation::Individ(size_t i)
{
     if(i< ptPopulationSize)return &ptIndivid[i];
     else return NULL;
};
//************************************************************************************************/
size_t BAPPopulation::MaxIndexIndivid()const
{
    return ptMaxIndexIndivid;
};
//************************************************************************************************/
size_t BAPPopulation::MinIndexIndivid()const
{
    return ptMinIndexIndivid;
};
//************************************************************************************************/
size_t BAPPopulation::GetMaxIndexIndivid()
{
    ptMaxIndexIndivid=Population::GetMaxIndexIndivid();
    return ptMaxIndexIndivid;
};
//************************************************************************************************/
size_t BAPPopulation::GetMinIndexIndivid()
{
    ptMinIndexIndivid=Population::GetMinIndexIndivid();
    return ptMinIndexIndivid;
};
//************************************************************************************************/
void BAPPopulation::SetSize(size_t x)
{
    ptSize=x;
    GetMemory();
};
//************************************************************************************************/
 void BAPPopulation::FreeAllMemory()
 {
     FreeMemory();
     Population::FreeAllMemory();
 };
//************************************************************************************************/
 #endif
