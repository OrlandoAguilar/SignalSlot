#pragma once
namespace siglot{
	template<typename tReturn, typename... args>
	class Callable{
	public:
		virtual tReturn operator()(args... a) = 0;
		virtual ~Callable(){}
		virtual bool Equal(Callable const&) = 0;
	};
}