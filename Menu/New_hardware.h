// header file New_hardware.h
// this is the specification of the class New_hardware，New_red_led，New_green_led
//New_hardware is parent class, New_red_led and New_green_led are child class
#include "Arduino.h"
//this classes used to add new green led or red led
class New_hardware{
  private:
  int new_pin=0;
  
  public:
  void give_low();
  void give_high();
  int get_new_pin();
  void set_new_pin(int input_pin);
};
class New_red_led:private New_hardware
{
  public:
  New_red_led(int input_pin);
  void ledon();
  void ledoff();
};
class New_green_led:private New_hardware
{
  public:
  New_green_led(int input_pin);
  void ledon();
  void ledoff();
};
