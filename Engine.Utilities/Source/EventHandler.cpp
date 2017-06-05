#include "Utilities\Event\EventHandler.h"

#include "Utilities\Utilities.h"


namespace Core
{
	EventHandler *EventHandler::m_SharedInstance = nullptr;
	
	EventHandler* EventHandler::StaticClass()
	{
		if (m_SharedInstance == nullptr)
		{
			m_SharedInstance = new EventHandler();
		}

		return m_SharedInstance;
	}

	void EventHandler::Release()
	{
		delete m_SharedInstance;
		m_SharedInstance = nullptr;
	}

	EventHandler::~EventHandler()
	{
		m_Subscribers.clear();
		m_Events.clear();
	}
	
	void EventHandler::Subscribe(Callback a_CallBack, EEvents a_To)
	{
		if (a_CallBack == nullptr)
		{
			LogErr("Error Callback was nullptr");
			return;
		}

		if (m_Subscribers.find(a_To) == m_Subscribers.end())
		{
			std::vector<Callback> vector;
			vector.push_back(a_CallBack);

			//For each event there is an set. One event can have multiple subscribers.
			m_Subscribers.insert( { a_To, vector } );
		}
		else
		{
			m_Subscribers[a_To].push_back(a_CallBack);
		}
	}

	void EventHandler::Unsubscribe(Callback a_CallBack, EEvents a_To)
	{
		if (m_Subscribers.find(a_To) != m_Subscribers.end())
		{
			int index = 0;
			auto arr = m_Subscribers[a_To];

			for (auto temp : arr)
			{
				//printf("%d %d\n", temp.target_type(), a_CallBack.target_type());

				if (temp.target_type() == a_CallBack.target_type())
				{
					m_Subscribers[a_To].erase(m_Subscribers[a_To].begin() + index);
				}
				index++;
			}
		}
		else
		{
			LogErr("Can't unsubscribe. Subscriber is not registered"); 
		}
	}

	void EventHandler::AddEvent(SEventDesc &a_Event)
	{
		m_Events.push_back(a_Event);
	}

	void EventHandler::ForceEvent(SEventDesc &a_Event)
	{
		for (auto temp : m_Subscribers[a_Event.Event])
		{
			temp(a_Event);
		}
	}

	void EventHandler::Update()
	{
		if (m_Events.size() > 0)
		{
			size_t size = m_Events.size() - 1; //because of pop_back

			for (auto temp : m_Subscribers[m_Events[size].Event])
			{
				temp(m_Events[size]);
			}

			m_Events.pop_back();
		}
	}
}