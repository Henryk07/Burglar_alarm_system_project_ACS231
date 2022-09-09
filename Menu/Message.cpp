// implementation file Message.cpp
// this is the implementation of the class Message
/* this class used to check serial and run all hardwares to prevent the information block */
#include "Message.h"

m_Message::m_Message(m_hardware *Hardwareobj) //Get the object pointer from the Menu
{
  
  this->Hardwareobjfrommessage=Hardwareobj; //Ensuring that the system changing is not blocked while waiting for user input
};
/*wait for message return true when the message in the buffer is ready*/
int m_Message::check_buffer()
{
  int m_buf=0;
  while(!m_buf)
  {
  //prevent input block the fix time funciton and system change
  this->Hardwareobjfrommessage->Hardwarework();
  if(Serial.available() > 0){
          //Read character
         m_buf = 1;
      }
  }
  return m_buf;
}
m_Message::~m_Message()
{
  
};
