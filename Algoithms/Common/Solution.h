#ifndef hpp_Solution_hpp
#define hpp_Solution_hpp

#include <time.h>
#include "..\..\Interface\ISolver.h"
#include "..\..\Interface\IGenerative.h"
#include "..\..\Interface\ICompareable.h"
#include "..\..\Interface\ICopyable.h"
#include "..\..\Interface\ICloneable.h"
#include "..\..\Interface\IRemoveable.h"

class Solution:public ICompareable, public IGenerative, public ICopyable, public ICloneable, public IRemoveable
{
    private:
        void __FreeMemory();
    public:
        clock_t tTime;

        Solution();
        Solution(const Solution&);
        void operator = (const Solution&);
        virtual ~Solution();

        float fSecond();
        float fMinute();
        float fHour();

        int iSecond();
        int iMinute();
        int iHour();

        virtual void SetValue(ISolver*)=0;
};

#endif
