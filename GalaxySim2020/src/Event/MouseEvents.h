#pragma once
#include "Corepch.h"
#include "Math/MVec.h"
#include "BaseClasses/Event.h"
namespace Application
{
	class MouseEvent : public Event
	{
	protected:
		const Vec2f m_cursorPos;
	protected:
		MouseEvent (EventType eventType, float cursorX, float cursorY)
			:Event (eventType, CatInputEvent | CatMouseEvent), m_cursorPos ({cursorX, cursorY})
		{}
	public:
		virtual EventType getEventType () const override = 0;
		virtual std::string getName () const override = 0;
		inline Vec2f getCursorPos () const { return m_cursorPos; }
	};
	enum class MouseKeyCode
	{
		MouseButtonL = VK_LBUTTON,
		MouseButtonR = VK_RBUTTON,
		MouseButtonM = VK_MBUTTON,
	};
	class MousePressedEvent : public MouseEvent
	{
	protected:
		MouseKeyCode m_keyCode;
	public:
		MousePressedEvent (MouseKeyCode mkc, float cursorX, float cursorY)
			:MouseEvent (EventType::MousePressed, cursorX, cursorY), m_keyCode (mkc)
		{}
		inline MouseKeyCode getKeyCode () { return m_keyCode; }
		inline EventType getEventType () const override { return m_eventType; }
		inline std::string getName () const override { return "MousePressedEvent"; }
		#ifdef DEBUG
		inline std::string toString () const override
		{
			return "Mouse key" + std::to_string ((int) m_keyCode) + " pressed at X : "
				+ std::to_string (m_cursorPos.x) + " Y: " + std::to_string (m_cursorPos.y);
		}
		#endif //DEBUG
	};

	class MouseReleasedEvent : public MouseEvent
	{
	protected:
		MouseKeyCode m_keyCode;
	public:
		MouseReleasedEvent (MouseKeyCode mkc, float cursorX, float cursorY)
			:MouseEvent (EventType::MouseReleased, cursorX, cursorY), m_keyCode (mkc)
		{}
		inline MouseKeyCode getKeyCode () { return m_keyCode; }
		inline EventType getEventType () const override { return m_eventType; }
		inline std::string getName () const override { return "MousePressedEvent"; }
		#ifdef DEBUG
		inline std::string toString () const override
		{
			return "Mouse key" + std::to_string ((int)m_keyCode) + " released at X : "
				+ std::to_string (m_cursorPos.x) + " Y: " + std::to_string (m_cursorPos.y);
		}
		#endif // DEBUG
	};
	class MouseScrollEvent : public MouseEvent
	{
	protected:
		Vec2f m_dScroll;
	public:
		MouseScrollEvent (MouseKeyCode mkc, float cursorX, float cursorY, float scrollX, float scrollY)
			:MouseEvent (EventType::MouseScrolled, cursorX, cursorY), m_dScroll ({ scrollX, scrollY })
		{}
		inline Vec2f getScrollY () { return m_dScroll; }
		inline EventType getEventType () const override { return m_eventType; }
		inline std::string getName () const override { return "MousePressedEvent"; }
		#ifdef DEBUG
		inline std::string toString ()const  override
		{
			return "Mouse scrolled at X : " + std::to_string (m_cursorPos.x) + " Y: " + std::to_string (m_cursorPos.y)
				+ " Scroll delta X: " + std::to_string (m_dScroll.x) + " scroll delta Y: " + std::to_string (m_dScroll.x);
		}
		#endif // DEBUG
	};
}