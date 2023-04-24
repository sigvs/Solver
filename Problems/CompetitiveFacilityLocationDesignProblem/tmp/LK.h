#pragma once

#include <memory>
#include "defs.h"


class LinKernighan: public INeighborhood
{
public:
	// nh --- заданная окрестность
	// objF --- так как нам надо искать оптимум в окрестности, целевая тоже нужна
	// max_try --- сколько точек в nh мы будем перебирать
	LinKernighan(const INeighborhood& nh, ObjectiveFunction objF, int max_try);

	LinKernighan* clone() const override;
	bool next(iVector& fv, int S) override;
	void prev(iVector& fv) override;
	void accept() override;

private:
	typedef std::shared_ptr<INeighborhood>	Neighborhood;

	Neighborhood		__nh;
	ObjectiveFunction	__objF;
	int					__max_try;
	iVector				__prev;
};
