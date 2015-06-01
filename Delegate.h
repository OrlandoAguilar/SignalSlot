#pragma once
#include "Callable.h"

namespace siglot{
	template<typename tClass, typename tReturn, typename... args>
	class Delegate :public Callable < tReturn, args... > {
		typedef tReturn(tClass::* tMethod)(args...);
	public:

		Delegate(tClass *_oClass, tMethod _method) :
			m_oClass(_oClass),
			m_method(_method)
		{}

		void ChangeMethod(tMethod _method){
			m_method = _method;
		}

		void ChangeClass(tClass *_oClass){
			m_oClass = _oClass;
		}
		tReturn operator()(args... a) override{
			return (m_oClass->*m_method)(a...);
		}

		bool operator==(Delegate const & pD) const{
			return m_oClass == pD.m_oClass && m_method == pD.m_method;
		}

		bool Equal(Callable const& _c) override{
			try{
				auto del = dynamic_cast<Delegate<tClass,tReturn, args...> const &> (_c);
				return del == *this;
			}
			catch (...){}
			return false;
		}

	private:
		tClass *m_oClass;
		tMethod m_method;
	};
}