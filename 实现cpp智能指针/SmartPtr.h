#ifndef SMARTPTR_H
#define SMARTPTR_H
template <typename T>
class SmartPtr{
public:
	SmartPtr(T* ptr = nullptr);
	SmartPtr(const SmartPtr& sptr);
	SmartPtr& operator = (const SmartPtr& sptr);
	~SmartPtr();
	T& operator* ();
	T* operator -> ();
	size_t use_count();
private:
	T* _ptr;
	size_t* _rf_count;
	void releaseCount();
};
#endif


template<typename T>
inline SmartPtr<T>::SmartPtr(T* ptr):_ptr(ptr),_rf_count(new size_t)
{
	if (ptr)
		* _rf_count = 1;
	else
		*_rf_count = 0;
}

template<typename T>
inline SmartPtr<T>::SmartPtr(const SmartPtr& sptr)
{
	if (this != &sptr) {
		_ptr = sptr._ptr;
		_rf_count = sptr._rf_count;
		(*_rf_count)++;
	}
}

template<typename T>
inline SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& sptr)
{
	if (this != &sptr) {
		releaseCount();
		_ptr = sptr._ptr;
		_rf_count = sptr._rf_count;
		(*_rf_count)++;
	}
	return *this;
}

template<typename T>
inline SmartPtr<T>::~SmartPtr()
{
	if (--(*_rf_count) == 0) {
		delete _ptr;
		delete _rf_count;
	}	
}

template<typename T>
inline T& SmartPtr<T>::operator*()
{
	if (_ptr)
		return *_ptr;
}

template<typename T>
inline T* SmartPtr<T>::operator->()
{
	if (_ptr)
		return _ptr;
}

template<typename T>
inline size_t SmartPtr<T>::use_count()
{
	return *_rf_count;
}

template<typename T>
inline void SmartPtr<T>::releaseCount()
{
	if (_ptr) {
		(*_rf_count)--;
		if ((*_rf_count) == 0) {
			delete _ptr;
			delete _rf_count;
		}
	}
}
