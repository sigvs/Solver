#include "util.h"


std::ostream& operator<< (std::ostream& os, const iPair& p)
{
	return os << "(" << p.first << ", " << p.second << ")";
}
