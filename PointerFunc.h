#pragma once
#include "Callable.h"

namespace siglot{
	template<typename tReturn, typename... args>
	class PointerFunc :public Callable < tReturn, args... > {
		typedef tReturn(*tPFunc)(args...);
	public:

		PointerFunc(tPFunc _tPF) :
			m_pFunc(_tPF)
		{}

		tReturn operator()(args... a) override{
			return (*m_pFunc)(a...);
		}

		bool operator==(PointerFunc const & pf) const{
			return m_pFunc == pf.m_pFunc;
		}

		bool Equal(Callable const& _c) override{
			try{
				auto pF = dynamic_cast<PointerFunc<tReturn, args...> const &> (_c);
				return pF == *this;
			}
			catch (...){}
			return false;
		}

	private:
		tPFunc m_pFunc;
	};
}