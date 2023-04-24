#pragma once


#include <vector>


typedef std::vector<int>					iVector;
typedef std::vector<double>					dVector;
typedef std::vector<std::vector<double>>	dMatrix;


using ObjectiveFunction = double (*)(const iVector&);


class INeighborhood
{
public:
	virtual ~INeighborhood() = 0;

	virtual INeighborhood* clone() const = 0;

	virtual bool next(iVector&, int) = 0;
	virtual void prev(iVector&) = 0;
	virtual void accept() = 0;
};
