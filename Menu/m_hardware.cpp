// implementation file m_hardware.cpp
// this is the implementation of the class m_hardware
/* this class used to read sensor and let hardwares work depends on the data get from sensor and also the time limit for the buzzer working */
#include "m_hardware.h"
m_hardware::m_hardware(){
  
};
m_hardware::~m_hardware(){
  
};
int m_hardware::Hardwarework(){
  double now_time=millis(); //Start Timer
  double timedelay=now_time-turnon_time; // Calculating the time since hardware was activated
  //PIR
  if(buzzerstatus&&(timedelay>buzzerdelay_time)&&this->m_Solenoidstatus)//Giving some time for the user to leave the house after the system is activated
  { 
    if(digitalRead(this->m_PIR)&&PIRstatus)//Checks if PIR detects movement 
    {
      //set_m_PIRdetected();
      if(lastonce==0)
      {
        lasttonetime=millis();
        lastonce=1;
      }
      tone(this->m_buzzer,500); //Activate buzzer at 500Hz
      red_led_arrays_on(); //RED LEDS on
      //turn off buzzer after 20 seconds
      check_buzzer_cutoff(now_time); //Deactivate buzzer for noise pollution
    }
    else
    {
      set_m_magswitchnotdetected();
      //noTone(this->m_buzzer);
      red_led_arrays_off();
    };
  }else if(!buzzerstatus) //if buzzer deactivated
  {
  //noTone(this->m_buzzer);
  red_led_arrays_off();
  };
  //magswitch
  if(buzzerstatus&&(timedelay>buzzerdelay_time))//delay 2000ms to start detected this->buzzerstatus/*&&((millis()-turnon_time)>5000)*/
  { 
    if(magswitchstatus&&digitalRead(this->m_magswitch))
    {
      //set_m_PIRdetected();
      if(lastonce==0)
      {
        lasttonetime=millis();
        lastonce=1;
      }
      tone(this->m_buzzer,500);
      red_led_arrays_on();
      //turn off buzzer after 5 seconds
      check_buzzer_cutoff(now_time);
    }
    else
    {
      set_m_PIRnotdetected();
      //noTone(this->m_buzzer);
      red_led_arrays_off();
    };
  }else if(!buzzerstatus)
  {
  //noTone(this->m_buzzer);
  red_led_arrays_off();
  };
};
void m_hardware::hardwareinitialize()
{
  pinMode(this->m_buzzer,OUTPUT);
  pinMode(this->m_PIR,INPUT);
  pinMode(this->m_magswitch,INPUT_PULLUP);
  pinMode(this->m_Solenoid,OUTPUT);
  //digitalWrite(this->m_PIR,LOW);
};
double m_hardware::get_delay_time()
{
  return this->buzzerdelay_time;
};
int m_hardware::check_buzzer_cutoff(double n_time)
{
  if((n_time-lasttonetime)>buzzerlimited_time)
  {
    noTone(this->m_buzzer);
    this->buzzerstatus=0;
    lastonce=0;
    green_led_arrays_off();
  }
  return 1;
}
void m_hardware::close_buzzer()
{
  noTone(this->m_buzzer);
};
int m_hardware::closeSensor(){
  this->buzzerstatus=0;
};
void m_hardware::setsystemstatus(int m_status)
{
  this->systemstatus=m_status;
};
void m_hardware::setbuzzerstatus(int m_status)
{
  this->buzzerstatus=m_status;
};
void m_hardware::set_turnon_time()
{
  this->turnon_time=millis();
};
void m_hardware::setPIRstatus(int m_status)
{
  this->PIRstatus=m_status;
};
int m_hardware::getbuzzerstatus()
{
  return this->buzzerstatus;
};
void m_hardware::setmagswitchstatus(int m_status)
{
  this->magswitchstatus=m_status;
};
int m_hardware::getPIRstatus()
{
  return this->PIRstatus;
};
int m_hardware::getPIR()
{
  return this->m_PIR;
}
int m_hardware::getm_PIR(){
  return this->m_PIR;
};
int m_hardware::getmagswitch()
{
  return this->m_magswitch;
};
int m_hardware::close_Solenoid()
{
  digitalWrite(this->m_Solenoid,HIGH);
};
int m_hardware::open_Solenoid()
{
  digitalWrite(this->m_Solenoid,LOW);
};
int m_hardware::get_m_magswitchdetected()
{
  return this->m_magswitchdetected;
};
int m_hardware::get_m_PIRdetected()
{
  return this->m_PIRdetected;
};
int m_hardware::getbuzzer()
{
  return this->m_buzzer;
};
void m_hardware::set_m_Solenoidstatus(int m_status)
{
  this->m_Solenoidstatus=m_status;
};
int m_hardware::get_m_Solenoidstatus()
{
  return this->m_Solenoidstatus;
};
void m_hardware::set_m_magswitchdetected()
{
    this->m_magswitchdetected=1;
};
void m_hardware::set_m_PIRdetected()
{
    this->m_PIRdetected=1;
};
void m_hardware::set_m_magswitchnotdetected()
{
    this->m_magswitchdetected=0;
};
void m_hardware::set_m_PIRnotdetected()
{
    this->m_PIRdetected=0;
};
void m_hardware::add_newredled(int pin)
{
  redledlist[current_red_led_index]=new New_red_led(pin);
  current_red_led_index=current_red_led_index+1;
};
void m_hardware::add_newgreenled(int pin)
{
  greenledlist[current_green_led_index]=new New_green_led(pin);
  current_green_led_index=current_green_led_index+1;
};
void m_hardware::red_led_arrays_on()
{
  for(int i=0;i<99;i++)
  {
    if(redledlist[i]!=NULL)
    {
      redledlist[i]->ledon();
    }else if(redledlist[i]==NULL)
    {
      break;
    }
  }
};
void m_hardware::red_led_arrays_off()
{
  for(int i=0;i<99;i++)
  {
    if(redledlist[i]!=NULL)
    {
      redledlist[i]->ledoff();
    }else if(redledlist[i]==NULL)
    {
      break;
    }
  }
};
void m_hardware::green_led_arrays_on()
{
  for(int i=0;i<99;i++)
  {
    if(greenledlist[i]!=NULL)
    {
      greenledlist[i]->ledon();
    }else if(greenledlist[i]==NULL)
    {
      break;
    }
  }
};
void m_hardware::green_led_arrays_off()
{
  for(int i=0;i<99;i++)
  {
    if(greenledlist[i]!=NULL)
    {
      greenledlist[i]->ledoff();
    }else if(greenledlist[i]==NULL)
    {
      break;
    }
  }
};
