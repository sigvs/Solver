#include <cstdlib>
#include "ExchangeOfVariants.h"

ExchangeOfVariants* ExchangeOfVariants::clone() const
{
	return new ExchangeOfVariants(*this);
}

bool ExchangeOfVariants::next(iVector& fv, int S)
{
	// выбираем открытые
	iVector opened;
	for (int i = 0; i < S; ++i) {
		if (fv[i] > 0) {
			opened.push_back(i);
		}
	}
	if (opened.empty()) {
		return false;
	}
	// выбираем закрытые
	iVector closed;
	for (int i = 0; i < S; ++i) {
		if (fv[i] == 0) {
			closed.push_back(i);
		}
	}
	if (closed.empty()) {
		return false;
	}
	// выбираем кандидатов на обмен
	__close = closed[std::rand() % closed.size()];
	__open = opened[std::rand() % opened.size()];
	// обмениваем их местами
	auto t = fv[__close];
	fv[__close] = fv[__open];
	fv[__open] = t;
	return true;
}

void ExchangeOfVariants::prev(iVector& fv)
{
	auto t = fv[__close];
	fv[__close] = fv[__open];
	fv[__open] = t;
}

void ExchangeOfVariants::accept()
{
}
