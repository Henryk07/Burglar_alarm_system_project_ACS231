// implementation file m_keypad.cpp
// this is the implementation of the class m_keypad
/* this class used to save the password, compare the password and check the attempts of entry, if attempts more than 3 times then lock the system*/
#include "m_keypad.h"

m_keypad::m_keypad(){
  
};
m_keypad::~m_keypad(){
  
};
int* m_keypad::getm_pin(){

    return this->m_PIN;
};
void m_keypad::setm_pin(int pin1,int pin2)
{
  int pin[4]={0};
  //pin1=pin1^15;
  //pin2=pin2^15;
  pin[3]=(int)pin2%10;
  pin[2]=(int)(pin2/10);
  pin[1]=(int)(pin1%10);
  pin[0]=(int)(pin1/10);
  for(int i=0;i<4;i++)
  {
    this->m_PIN[i]=pin[i];
  }
};
int m_keypad::cmp_pin(int pin1,int pin2){
  int pin[4]={0};
  //pin1=pin1^15;
  //pin2=pin2^15;
  pin[3]=(int)pin2%10;
  pin[2]=(int)(pin2/10);
  pin[1]=(int)(pin1%10);
  pin[0]=(int)(pin1/10);
    for(int i=0;i<4;i++)
    {
      if(pin[i]!=this->m_PIN[i])
      {
        return 0;
      }
    }
    return 1; //1 means correct pin
};
int m_keypad::set_attempts()
{
  sys_attempts=sys_attempts+1;
  if((this->sys_attempts)==max_attempts)
  {
  this->lastlock_time=millis();
  }
  return 1;
}
int m_keypad::check_attempts()
{
  return (this->sys_attempts)<max_attempts;
}
int m_keypad::check_locktime()
{
  if(millis()-lastlock_time>10000)
  {
    this->lastlock_time=0;
    this->sys_attempts=0;
  }
}
int m_keypad::clean_attempts()
{
  this->sys_attempts=0;
}
