#pragma once
#include "Callable.h"

namespace siglot{
	template<typename... args>
	class Slot;

	template<typename... args>
	class Signal{
		typedef Slot<args...> tSlot;
		friend class tSlot;
	public:
		void operator()(args... ar){
			for (auto slot : m_slots){
				(*slot)(ar...);
			}
		}

		void Connect(tSlot* slot){
			AppendSlot(slot);
			slot->AppendSignal(this);
		}

		void Disconnect(tSlot* slot){
			RemoveSlot(slot);
			slot->RemoveSignal(this);
		}
		~Signal(){
			for (tSlot* slot : m_slots){
				slot->RemoveSignal(this);
			}
		}
	private:
		void AppendSlot(tSlot* slot){
			m_slots.push_back(slot);
		}
		void RemoveSlot(tSlot* slot){
			m_slots.remove(slot);
		}
		std::list< tSlot*> m_slots;
	};
}