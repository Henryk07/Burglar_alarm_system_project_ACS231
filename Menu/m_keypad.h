// header file m_keypad.h
// this is the specification of the class m_keypad
#include "Arduino.h"
class m_keypad{
  private:
    int m_PIN[4]={6,5,8,1};
    const int max_attempts=3;
    double lastlock_time=0;
    int lockstatus=0;
    int sys_attempts=0;
  public:
    int check_locktime();
    int set_attempts();
    int check_attempts();
    int clean_attempts();
    int* getm_pin();
    int  cmp_pin(int pin1,int pin2);
    void setm_pin(int pin1,int pin2);
    m_keypad();
    ~m_keypad();
  
};
