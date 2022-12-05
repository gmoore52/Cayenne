#include "Event.h"

#ifndef CAYENNETESTPROJECT_KEYEVENT_H
#define CAYENNETESTPROJECT_KEYEVENT_H

namespace Cayenne {

    class CY_API KeyEvent : public Event
    {
        public:
        inline int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
    KeyEvent(int keycode)
            : m_KeyCode(keycode) {}

    int m_KeyCode;
    };

    class CY_API KeyPressedEvent : public KeyEvent
    {
    public:
    KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

    inline int GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override
    {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
    return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
    private:
    int m_RepeatCount;
    };

    class CY_API KeyReleasedEvent : public KeyEvent
    {
    public:
    KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

    std::string ToString() const override
    {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
    };
}

#endif //CAYENNETESTPROJECT_KEYEVENT_H
