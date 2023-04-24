#include <fstream>
#include "LK.h"
#include "util.h"
#include "VNS.h"
#include <iostream>


VNS& VNS::operator+= (const INeighborhood& nh)
{
	__nl.emplace_back(nh.clone());
	return *this;
}


/*double VNS::findMaximum(ObjectiveFunction objectiveFunction, iVector& fv, int S, iVector& opt)
{
	static int MAX_TRY = 100;
	iVector total(__nl.size(), 0);
	iVector accepted(__nl.size(), 0);
	int nnh;	// number of neighborhood

	double currValue = objectiveFunction(fv), maxValue = currValue;
	opt = fv;
	const auto& beg = __nl.begin(), end = __nl.end();
	auto nh = beg;
	nnh = 0;
	bool findBetter;
	// просматриваем окрестности
	while (nh != end) {
		int ntry = 0;
		findBetter = false;
		// пробуем окрестность не более MAX_TRY раз
		while (!findBetter && ntry++ < MAX_TRY) {
			if (!(*nh)->next(fv, S)) {
				break;
			}
			double val = objectiveFunction(fv);
			++total[nnh];
			if (val > currValue) {
				// нашли решение лучше
				(*nh)->accept();
				++accepted[nnh];
				nnh = 0;
				nh = beg;
				findBetter = true;
				currValue = val;
			} else {
				// откатываем назад
				(*nh)->prev(fv);
			}
			if (currValue > maxValue) {
				opt = fv;
				maxValue = currValue;
			}
		}
		// если не нашли лучше, переходим к следующей окрестности
		if (!findBetter) {
			++nh;
			++nnh;
		}
	}
	std::ofstream ofs_total("total.txt", std::ios_base::app);
	ofs_total << total << std::endl;
	std::ofstream ofs_accept("accept.txt", std::ios_base::app);
	ofs_accept << accepted << std::endl;
	return maxValue;
}*/

double VNS::findMaximum(ObjectiveFunction objectiveFunction,
	const INeighborhood& nhForLocalSearch, iVector& fv, int S, iVector& opt)
{
	static int MAX_TRY = 100;

	iVector total(__nl.size(), 0);
	iVector accepted(__nl.size(), 0);
	int nnh;	// number of neighborhood
	nnh = 0;

	double currValue = objectiveFunction(fv), maxValue = currValue;
	opt = fv;	// начальный рекорд
	const auto& beg = __nl.begin(), end = __nl.end();
	auto nh = beg;
	bool findBetter;
	// с помощью этой окрестности будем осуществлять поиск локального максимума
	LinKernighan lk(nhForLocalSearch, objectiveFunction, 9);
	// просматриваем окрестности
	while (nh != end) {
		int ntry = 0;
		findBetter = false;
		iVector temp;
		// пробуем окрестность не более MAX_TRY раз
		while (!findBetter && ntry++ < MAX_TRY) {
			if (!(*nh)->next(fv, S)) {
				break;
			}
			temp = fv;
			// выбрали точку;
			// теперь ищем локальный максимум
			lk.next(fv, S);
			double val = objectiveFunction(fv);
			++total[nnh];
			if (val > currValue) {
				// нашли решение лучше
				(*nh)->accept();
				++accepted[nnh];
				nnh = 0;
				nh = beg;
				findBetter = true;
				currValue = val;
			} else {
				// откатываем назад
				//(*nh)->prev(fv);
				fv = temp;
			}
			if (currValue > maxValue) {
				opt = fv;
				maxValue = currValue;
			}
		}
		// если не нашли лучше, переходим к следующей окрестности
		if (!findBetter) {
			++nh;
			++nnh;
		}
	}
	std::ofstream ofs_total("total.txt", std::ios_base::app);
	ofs_total << total << std::endl;
	std::ofstream ofs_accept("accept.txt", std::ios_base::app);
	ofs_accept << accepted << std::endl;
	return maxValue;
}
