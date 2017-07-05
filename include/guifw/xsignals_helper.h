#pragma once
#include "xsignals.h"


namespace xsignals_helper
{
	//////////////////////////////////////////////////////////////////////////
	//sig_connect(...)////////////////////////////////////////////////////////////////////////
	//calling syntax:  sig_connect(sig, this, &T::mfn)

	//for signal()
	template <class T, class R> inline 
	void sig_connect(xsignals::signal<R ()>& sig, 
					T* pThis, R (T::*mfn)() )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1)
	template <class T, class R, class A1> inline 
	void sig_connect(xsignals::signal<R (A1)>& sig, 
					T* pThis, R (T::*mfn)(A1) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2)
	template <class T, class R, class A1, class A2> inline 
	void sig_connect(xsignals::signal<R (A1, A2)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2, a3)
	template <class T, class R, class A1, class A2, class A3> inline 
	void sig_connect(xsignals::signal<R (A1, A2, A3)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2, A3) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2, a3, a4)
	template <class T, class R, class A1, class A2, class A3, class A4> inline 
	void sig_connect(xsignals::signal<R (A1, A2, A3, A4)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2, A3, A4) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2, a3, a4, a5)
	template <class T, class R, class A1, class A2, class A3, class A4, class A5> inline 
	void sig_connect(xsignals::signal<R (A1, A2, A3, A4, A5)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2, A3, A4, A5) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2, a3, a4, a5, a6)
	template <class T, class R, class A1, class A2, class A3, class A4, class A5, class A6> inline 
	void sig_connect(xsignals::signal<R (A1, A2, A3, A4, A5, A6)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2, A3, A4, A5, A6) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2, a3, a4, a5, a6, a7)
	template <class T, class R, class A1, class A2, class A3, class A4, class A5, class A6,class A7> inline 
	void sig_connect(xsignals::signal<R (A1, A2, A3, A4, A5, A6, A7)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2, A3, A4, A5, A6, A7) )
	{
		sig.connect(pThis, mfn);
	}

	//for signal(a1, a2, a3, a4, a5, a6, a7, a8)
	template <class T, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> inline 
	void sig_connect(xsignals::signal<R (A1, A2, A3, A4, A5, A6, A7, A8)>& sig, 
					T* pThis, R (T::*mfn)(A1, A2, A3, A4, A5, A6, A7, A8) )
	{
		sig.connect(pThis, mfn);
	}




	//sig_disconnect
	template <class Signature, class T> inline 
	void sig_disconnect(xsignals::signal<Signature>& sig, T* pThis)
	{
		sig.disconnect(pThis);
	}

/*	//sig_disconnect_all
	template <class Signature> inline 
	void sig_disconnect_all(xsignals::signal<Signature>& sig)
	{
		sig.disconnect_all();
	}
*/


	inline 
	void free_all_slots_of(xsignals::trackable* pTrackable)
	{
		pTrackable->disconnect_all();
	}


} //namespace xsignals_helper
