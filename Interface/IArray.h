#ifndef h_IArray_h
#define h_IArray_h
template <typename T>
class IArray
{
 public:
	 virtual size_t GetElementCount() = 0;
	 virtual T GetElement(size_t i) = 0;
	 virtual void SetElement(size_t i, T v) = 0;
};
#endif
