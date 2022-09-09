// header file m_Message.h
// this is the specification of the class m_Message

#include "Arduino.h"
#ifndef HARDWARE
#define HARDWARE
#include "m_hardware.h"
#endif
class m_Message{
  public:
  m_hardware *Hardwareobjfrommessage;
  m_Message(m_hardware *Hardwareobj);
  ~m_Message();
  int check_buffer();
};
