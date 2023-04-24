#include "LK.h"


LinKernighan::LinKernighan(const INeighborhood& nh, ObjectiveFunction objF, int max_try)
	: __nh(nh.clone()), __objF(objF), __max_try(max_try), __prev()
{
}


LinKernighan* LinKernighan::clone() const
{
	return new LinKernighan(*this);
}


bool LinKernighan::next(iVector& fv, int S)
{
	__prev = fv;
	iVector opt = fv;
	double maxValue = __objF(fv);
	for (int ntry = 0; ntry < __max_try; ++ntry) {
		if (!__nh->next(fv, S)) {
			break;
		}
		double val = __objF(fv);
		if (val > maxValue) {
			__nh->accept();
			opt = fv;
			maxValue = val;
		} else {
			__nh->prev(fv);
		}
	}
	fv = opt;
	return true;
}


void LinKernighan::prev(iVector& fv)
{
	fv = __prev;
}


void LinKernighan::accept()
{
}
