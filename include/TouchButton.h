#include <Bounce2.h>
class TouchButton : public Bounce2::Button
{
public:
  TouchButton(touch_value_t threshold) : _threshold(threshold)
  {
  }
  void reset()
  {
    stateChangeLastTime = millis();
  }

protected:
  touch_value_t _threshold;
  virtual void setPinMode(int pin, int mode)
  { /* do nothing */
  }
  virtual bool readCurrentState() { return touchRead(pin) < _threshold; }
};