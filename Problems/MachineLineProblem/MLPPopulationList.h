#ifndef hpp_MLPPopulationList_hpp
#define hpp_MLPPopulationList_hpp

#include "..\..\Algoithms\Evolutional\PopulationUseList.h"
#include "..\MachineLineProblem\MLPSolution.h"
#include <list>
class MLPPopulationList:public PopulationUseList
{
    public:
        void GetMemory();

        friend ofstream& operator <<(ofstream& , MLPPopulationList&);
        friend ifstream& operator >>(ifstream& , MLPPopulationList&);
        friend ostream& operator <<(ostream& , MLPPopulationList&);
};
#endif
