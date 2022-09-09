// implementation file New_hardware.cpp
// this is the implementation of the class New_hardware(parent) New_red_led(child) New_green_led(child)
/* this class used to add new hardware(green led and red led)*/
#include "New_hardware.h"

void New_hardware::give_low()
{
  digitalWrite(this->new_pin,LOW);
};
int New_hardware::get_new_pin()
{
  return this->new_pin;
};
void New_hardware::set_new_pin(int input_pin)
{
  this->new_pin=input_pin;
};
void New_hardware::give_high()
{
  digitalWrite(this->new_pin,HIGH);
};

New_red_led::New_red_led(int input_pin)
{
  New_hardware::set_new_pin(input_pin);
  pinMode(New_hardware::get_new_pin(),OUTPUT);
};
void New_red_led::ledon()
{
  digitalWrite(New_hardware::get_new_pin(),HIGH);
};
void New_red_led::ledoff()
{
  digitalWrite(New_hardware::get_new_pin(),LOW);
};

New_green_led::New_green_led(int input_pin)
{
  New_hardware::set_new_pin(input_pin);
  pinMode(New_hardware::get_new_pin(),OUTPUT);
};
void New_green_led::ledon()
{
  digitalWrite(New_hardware::get_new_pin(),HIGH);
};
void New_green_led::ledoff()
{
  digitalWrite(New_hardware::get_new_pin(),LOW);
};
