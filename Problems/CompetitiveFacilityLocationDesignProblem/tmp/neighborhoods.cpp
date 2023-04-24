#include <algorithm>
#include <cstdlib>
// #include <iostream>
#include "util.h"
#include "neighborhoods.h"


CloseFirstOpenBest::CloseFirstOpenBest(int S): __weight(S, 0)
{
}


CloseFirstOpenBest* CloseFirstOpenBest::clone() const
{
	return new CloseFirstOpenBest(*this);
}


bool CloseFirstOpenBest::next(iVector& fv, int S)
{
	int i = 0;
	while (i < S && fv[i] == 0) ++i;
	if (i == S) {
		return false;
	}
	int j = i + 1;
	while (j < S && fv[j] == 3) ++j;
	if (j == S) {
		return false;
	}
	int jmax = j;
	int wmax = __weight[j];
	while (j < S) {
		if (fv[j] < 3 && __weight[j] > wmax) {
			wmax = __weight[j];
			jmax = j;
		}
		++j;
	}
	__close = i; __open = jmax;
	--fv[__close]; ++fv[__open];
	// std::cout << "1 next: " << fv << std::endl;
	return true;
}


void CloseFirstOpenBest::prev(iVector& fv)
{
	// std::cout << "- rejected" << std::endl;
	--__weight[__open];
	--__weight[__close];
	++fv[__close];
	--fv[__open];
}


void CloseFirstOpenBest::accept()
{
	// std::cout << "+ accepted" << std::endl;
	++__weight[__open];
	++__weight[__close];
}


// CloseRandomOpenBest
CloseRandomOpenBest::CloseRandomOpenBest(int S): __weight(S, 0)
{
}


CloseRandomOpenBest* CloseRandomOpenBest::clone() const
{
	return new CloseRandomOpenBest(*this);
}


bool CloseRandomOpenBest::next(iVector& fv, int S)
{
	iVector indexes;
	for (int i = 0; i < S; ++i) {
		if (fv[i]) {
			indexes.push_back(i);
		}
	}
	if (indexes.size() == 0 || indexes.size() == (unsigned)S) {
		return false;
	}
	// закрываем случайный
	__close = indexes[std::rand() % indexes.size()];
	// открываем самый хороший
	int j = 0;
	while (j < S && fv[j]) ++j;
	int wmax = __weight[j];
	__open = j;
	for (++j; j < S; ++j) {
		if (fv[j] == 0 && j != __close && __weight[j] > wmax) {
			wmax = __weight[j];
			__open = j;
		}
	}
	fv[__open] = fv[__close];
	fv[__close] = 0;
	// std::cout << "2 next: " << fv << std::endl;
	return true;
}


void CloseRandomOpenBest::prev(iVector& fv)
{
	// std::cout << "- rejected" << std::endl;
	--__weight[__open];
	--__weight[__close];
	++fv[__close];
	--fv[__open];
}


void CloseRandomOpenBest::accept()
{
	// std::cout << "+ accepted" << std::endl;
	++__weight[__open];
	++__weight[__close];
}


// CloseRandomOpenRandom
CloseRandomOpenRandom* CloseRandomOpenRandom::clone() const
{
	return new CloseRandomOpenRandom(*this);
}


// random int in [a, b]
int uniform(int a, int b)
{
	return a + std::rand() % (b - a + 1);
}


bool CloseRandomOpenRandom::next(iVector& fv, int S)
{
	iVector openable;
	for (int i = 0; i < S; ++i) {
		if (fv[i] < 3) {
			openable.push_back(i);
		}
	}
	if (openable.empty()) {
		return false;
	}
	iVector closeable;
	for (int i = 0; i < S; ++i) {
		if (fv[i] > 0) {
			closeable.push_back(i);
		}
	}
	if (closeable.empty()) {
		return false;
	}
	__close = closeable[std::rand() % closeable.size()];
	__open = openable[std::rand() % openable.size()];
	__dr = uniform(1, std::min(fv[__close], 3 - fv[__open]));
	fv[__close] -= __dr;
	fv[__open] += __dr;
	return true;
}


void CloseRandomOpenRandom::prev(iVector& fv)
{
	fv[__close] += __dr;
	fv[__open] -= __dr;
}


void CloseRandomOpenRandom::accept()
{
}


// RandomShuffle
RandomShuffle::RandomShuffle(int S): __prev(S, 0)
{
}


RandomShuffle* RandomShuffle::clone() const
{
	return new RandomShuffle(*this);
}


bool RandomShuffle::next(iVector& fv, int S)
{
	// std::cout << "RandomShuffle " << fv << " -> ";
	__prev = fv;
	std::random_shuffle(fv.begin(), fv.begin() + S);
	// std::cout << fv << std::endl;
	return true;
}


void RandomShuffle::prev(iVector& fv)
{
	fv = __prev;
}


void RandomShuffle::accept()
{
}
