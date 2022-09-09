// implementation file fr.cpp
// this is the implementation of the class m_fr
/* this class used to check the attempts of facial recognition and lock time*/
#include "fr.h"
#include "Arduino.h"
int m_fr::check_works()
{
  
  
}

int m_fr::check_lockstatus() //check if system is locked
{
  return this->lockstatus;
}
int m_fr::check_attempts()
{
  return this->sys_attempts<max_attempts; //check if attempts reached maximum attempts
}
int m_fr::set_attempts()
{
  this->sys_attempts=this->sys_attempts+1; //increasing attempts count
  this->lastlock_time=millis();
  return 1;
}

int m_fr::check_locktime() //Lock System for 10 minutes
{
  if(millis()-lastlock_time>10000)
  {
    this->lastlock_time=0;
    this->sys_attempts=0;
  }
}
