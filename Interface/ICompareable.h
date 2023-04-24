#ifndef h_ICompareable_h
#define h_ICompareable_h

class ICompareable
{
 public:
	 virtual bool bEqual(void*)const = 0;
	 virtual bool bNotEqual(void*)const = 0;
	 virtual bool bBetter(void*)const = 0;
	 virtual bool bBetterOrEqual(void*)const = 0;
	 virtual bool bWorse(void*)const = 0;
	 virtual bool bWorseOrEqual(void*)const = 0;
	 virtual bool bIdentical(void*)const = 0;
	 virtual bool bNotIdentical(void*)const = 0;
};
#endif
