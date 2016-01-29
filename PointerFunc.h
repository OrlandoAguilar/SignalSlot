#pragma once

/*
Copyright 2015 Orlando Aguilar Vivanco

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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