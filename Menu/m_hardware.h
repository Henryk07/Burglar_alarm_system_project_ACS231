// header file m_hardware.h
// this is the specification of the class m_hardware
#include "Arduino.h"
#include "New_hardware.h"
class m_hardware{
  private:
  int m_buzzer=12;
  int m_PIR=5;
  int m_Solenoid=9;
  int m_magswitch=3;
  int lastdetecttime=0;
  int buzzerstatus=0;
  int PIRstatus=0;
  int systemstatus=0;
  int magswitchstatus=0;
  double lasttonetime=0;
  int lastonce=0;
  int m_magswitchdetected=0;
  int m_PIRdetected=0;
  int m_Solenoidstatus=0;
  New_red_led *redledlist[100]={NULL};
  New_green_led *greenledlist[100]={NULL};
  int current_red_led_index=0;
  int current_green_led_index=0;
  const double buzzerlimited_time=20000;
  const double buzzerdelay_time=5000;
  public:
    double turnon_time=0;
    int Hardwarework();
    void hardwareinitialize();
    int closeSensor();
    void setsystemstatus(int m_status);
    void setbuzzerstatus(int m_status);
    void setPIRstatus(int m_status);
    void setmagswitchstatus(int m_status);
    int getbuzzerstatus();
    int getPIRstatus();
    int getbuzzer();
    int getPIR();
    int getmagswitch();
    int getm_PIR();
    int close_Solenoid();
    int open_Solenoid();
    int check_buzzer_cutoff(double n_time);
    void add_newredled(int pin);
    void add_newgreenled(int pin);
    void red_led_arrays_on();
    void red_led_arrays_off();
    void green_led_arrays_on();
    void green_led_arrays_off();
    void set_m_magswitchdetected();
    void set_m_PIRdetected();
    void set_m_magswitchnotdetected();
    void close_buzzer();
    void set_m_PIRnotdetected();
    void set_turnon_time();
    void set_m_Solenoidstatus(int m_status);
    int get_m_Solenoidstatus();
    int get_m_magswitchdetected();
    int get_m_PIRdetected();
    double get_delay_time();
    m_hardware();
    ~m_hardware();
};
