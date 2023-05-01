#ifndef hpp_CFLDPPopulationList_hpp
#define hpp_CFLDPPopulationList_hpp

#include "..\..\Algoithms\Evolutional\PopulationUseList.h"
#include "CFLDPSolution.h"
#include <list>
class CFLDPPopulationList:public PopulationUseList
{
    public:
        void GetMemory();

        friend ofstream& operator <<(ofstream& , CFLDPPopulationList&);
        //friend ifstream& operator >>(ifstream& , CFLDPPopulationList&);
        friend ostream& operator <<(ostream& , CFLDPPopulationList&);
};
#endif
