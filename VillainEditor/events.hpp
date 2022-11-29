#pragma once



enum class EventType
{
 MouseMove,
 MouseScroll,
 MouseButtonPressed,
 MouseButtonReleased,
 KeyPress,
 KeyRelease
};


class Event
{
public:
 virtual EventType getEventType() const = 0;
};

class KeyPressEvent :public Event
{
public:
 int key;
 KeyPressEvent(int k) :key(k) {};
 virtual EventType getEventType() const override
 {
  return EventType::KeyPress;
 };
};

class KeyReleaseEvent :public Event
{
public:
 int key;
 KeyReleaseEvent(int k) :key(k) {};
 virtual EventType getEventType() const override
 {
  return EventType::KeyRelease;
 };
};

struct CursorMoveEvent :public Event
{
 double xpos;
 double ypos;

 virtual EventType getEventType() const override
 {
  return EventType::MouseMove;
 };

};

struct MouseClickEvent
{
 int button;
 int action;
 int mods;
};
