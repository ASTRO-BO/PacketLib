/***************************************************************************
                          SharedPtr.h
                        -------------------
    begin                : Fri Dec 20 2013
    copyright            : (C) 2013 by Andrea Zoli
    email                : zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef __PACKETLIB_SHARED_PTR_H
#define __PACKETLIB_SHARED_PTR_H

namespace PacketLib
{

template<class T>
class SharedPtr
{
	template<class U>
	friend class SharedPtr;

	public:

	SharedPtr() : p(0), c(0) {}
	explicit SharedPtr(T* s) : p(s), c(new unsigned(1)) {}

	SharedPtr(void* null) : p(0), c(0) {}

	SharedPtr(const SharedPtr& s) : p(s.p), c(s.c) { if(c) ++*c; }

	template<class U>
	SharedPtr(const SharedPtr<U>& s) : p(s.p), c(s.c) { if(c) ++*c; }

	~SharedPtr() { clear(); }

	SharedPtr& operator=(const SharedPtr& s)
	{ if(this!=&s) { clear(); p=s.p; c=s.c; if(c) ++*c; } return *this; }

	typedef T* SharedPtr<T>::*unspecified_bool_type;
	operator unspecified_bool_type() const // never throws
	{
		return p == 0 ? 0 : &SharedPtr<T>::p;
	}

	void clear()
	{
		if(c)
		{
		    if(*c==1) delete p;
		    if(!--*c) delete c;
		}
		c=0; p=0;
	}

	T* get() const { return (c)? p: 0; }
	T* operator->() const { return get(); }
	T& operator*() const { return *get(); }

	private:

	T* p;
	unsigned* c;
};

}

#endif
