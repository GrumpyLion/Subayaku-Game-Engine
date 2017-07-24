#pragma once

#include "SEventDesc.h"

#include <unordered_map>
#include <set>
#include <vector>

#include <functional>

#include <memory>

typedef std::function<void(Core::SEventDesc&)> Callback;

namespace Core
{
	class EventHandler
	{
	private:
		std::vector<SEventDesc> m_Events;
		std::unordered_map<EEvents, std::vector<Callback>> m_Subscribers;

		static EventHandler *m_SharedInstance;

	public:
		~EventHandler();

		// The given function will be bound to this eventhandler. Everytime the given Event is processed, all bound functions will be called with a given struct.
		//
		__declspec(dllexport) void Subscribe(Callback a_CallBack, EEvents a_To);
		
		//
		//
		__declspec(dllexport) void Unsubscribe(Callback a_CallBack, EEvents a_To);
		
		__declspec(dllexport) void AddEvent(SEventDesc &a_Event);
		__declspec(dllexport) void ForceEvent(SEventDesc &a_Event);
		
		//In Update the events will be handled
		//
		__declspec(dllexport) void Update();

		__declspec(dllexport) static EventHandler* StaticClass();
		__declspec(dllexport) static void Release();
	};
}