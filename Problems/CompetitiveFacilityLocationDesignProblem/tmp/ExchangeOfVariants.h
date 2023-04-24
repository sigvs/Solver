#pragma once


#include "defs.h"


/// Окрестность, которая делает обмен вариантов функционирования:
/// закрытое меняет на открытое и наоборот
class ExchangeOfVariants : public INeighborhood
{
public:
	ExchangeOfVariants* clone() const override;

	bool next(iVector&, int) override;
	void prev(iVector&) override;
	void accept() override;

private:
	int		__open, __close;
};
