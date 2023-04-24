#pragma once


#include "defs.h"


class CloseFirstOpenBest: public INeighborhood
{
public:
	CloseFirstOpenBest(int S);

	CloseFirstOpenBest* clone() const override;
	bool next(iVector& fv, int S) override;
	void prev(iVector& fv) override;
	void accept() override;

private:
	int		__open, __close;
	iVector	__weight;
};


class CloseRandomOpenBest: public INeighborhood
{
public:
	CloseRandomOpenBest(int S);

	CloseRandomOpenBest* clone() const override;
	bool next(iVector& fv, int S) override;
	void prev(iVector& fv) override;
	void accept() override;

private:
	int		__open, __close;
	iVector	__weight;
};

class CloseRandomOpenRandom: public INeighborhood
{
public:
	CloseRandomOpenRandom* clone() const override;
	bool next(iVector& fv, int S) override;
	void prev(iVector& fv) override;
	void accept() override;

private:
	int	__open, __close, __dr;
};


class RandomShuffle: public INeighborhood
{
public:
	RandomShuffle(int S);

	RandomShuffle* clone() const override;
	bool next(iVector& fv, int S) override;
	void prev(iVector& fv) override;
	void accept() override;

private:
	iVector __prev;
};
