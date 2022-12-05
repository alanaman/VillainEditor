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
 int mods=0;
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

class MouseButtonPressEvent :public Event
{
public:
 int button;
 MouseButtonPressEvent(int b) :button(b) {};
 virtual EventType getEventType() const override
 {
  return EventType::MouseButtonPressed;
 };
};

class MouseButtonReleaseEvent :public Event
{
public:
 int button;
 MouseButtonReleaseEvent(int b) :button(b) {};
 virtual EventType getEventType() const override
 {
  return EventType::MouseButtonReleased;
 };
};

struct CursorMoveEvent :public Event
{
 double delta_x;
 double delta_y;

 CursorMoveEvent(double del_x, double del_y) :
  delta_x(del_x), delta_y(del_y)
 {};
 virtual EventType getEventType() const override
 {
  return EventType::MouseMove;
 };

};

