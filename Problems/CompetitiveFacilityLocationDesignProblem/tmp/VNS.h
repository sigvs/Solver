#pragma once


#include <memory>
#include "defs.h"


class VNS
{
public:
	VNS& operator+= (const INeighborhood&);

	double findMaximum(ObjectiveFunction, iVector& fv, int S, iVector& opt);
	double findMaximum(ObjectiveFunction, const INeighborhood& nh, iVector& fv, int S, iVector& opt);

private:
	typedef std::shared_ptr<INeighborhood>	Neighborhood;
	typedef std::vector<Neighborhood>		NeighborhoodList;

	NeighborhoodList __nl;
};
