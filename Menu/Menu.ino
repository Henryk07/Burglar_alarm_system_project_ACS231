/*Title: Burglar Alarm System Implementation for ACS233

Authors:
Jiazhen Haung 
Mohamed Saafan
Haolin Chen
Austin Ng

Date: 18/05/2022

Description:
This program is used to implement a burglar alarm system using communication between sensors, Arduino and MATLAB, and is written in C++. The objects used in this project are a magnetic sensor (for the window), Solenoid (for door lock), PIR sensor (for motion detection), WEBCAM (for facial recognition), keyboard (for user input, e.g., PIN), and a buzzer for alarming the user in case of burglary. A menu for the user is designed and is communicating to all other objects. 
*/
#include "Arduino.h"
#include "Message.h"
#ifndef HARDWARE
#define HARDWARE
#include "m_hardware.h"
#endif
#include "m_keypad.h"
#include "String.h"
#include "fr.h"
/*
 LED 2
 CHUANG SWITCH 3
 pir sensor 5
 men kaiguanjiance 9
 buzzer 12
 */

// Declaring System objects:
m_Message *m_messobj; //Object for communication between MATLAB and Arduinp
m_hardware *m_hardwareobj; // PIR, Selonid, and Magnetic sensor objects
m_keypad *m_keypadobj; // Object for keyboard
m_fr *m_frobj; //Facial Recognition (WEBCAM) Object
int waitfacial=0;

void setup() {
  Serial.begin(9600);
  //Setup of the object and giving the address of the object to their respective pointers
  m_hardwareobj=new m_hardware();
  m_messobj=new m_Message(m_hardwareobj);
  m_keypadobj=new m_keypad();
  m_frobj=new m_fr();
  m_hardwareobj->hardwareinitialize();
}

void loop() {
 // 
  m_hardwareobj->Hardwarework(); //Accessing the Hardware object to get inputs and execute outputs 
  
  //Exchanging hardware status wirh MATLAB
    if(m_messobj->check_buffer())  
    {
      //For Magnetic Sensor:
      Serial.read();
      if(digitalRead(m_hardwareobj->getmagswitch())/*m_hardwareobj->get_m_magswitchdetected()*/)
      {
        Serial.print('1');
      }else
      {
        Serial.print('0');
      }
    };
    if(m_messobj->check_buffer())
    {
      //For PIR:
      Serial.read();
      if(digitalRead(m_hardwareobj->getPIR())/*m_hardwareobj->get_m_PIRdetected()*/)
      {
        Serial.print('1');
      }else
      {
        Serial.print('0');
      }
    };

  
  if(!m_frobj->check_attempts()) //Counting Facial Recognition attempts
  {
  m_frobj->check_locktime(); //Recording The duration since the system was locked
  };
  if(!m_keypadobj->check_attempts()) //Counting nom. of PIN attempts
  {
  m_keypadobj->check_locktime(); //Recording the time passed since the system was locked
  }
  if(m_frobj->check_attempts()&&m_keypadobj->check_attempts()) //If the system is not locked
  { 
    //Reading Input PIN:
    int m_messagepin1=0; 
    int m_messagepin2=0;
    //Reading New (reset) input PIN:
    int m_newmessagepin1=0;
    int m_newmessagepin2=0;
    char path=0;
    //char m_order=Serial.read();
    if(m_messobj->check_buffer()) //Checking buffer
    {
      Serial.read();
      if(m_hardwareobj->getPIRstatus()&&digitalRead(m_hardwareobj->getPIR())&&m_frobj->check_attempts()&&((millis()-m_hardwareobj->turnon_time)>m_hardwareobj->get_delay_time()))
      {
        Serial.print('1');
        if(m_messobj->check_buffer())
        {
          waitfacial=Serial.read(); //Get Facial Recognition input
          if(waitfacial==1) //If user is detected
          {
            m_hardwareobj->set_m_Solenoidstatus(1);
            m_hardwareobj->close_Solenoid();
            //tone(m_hardwareobj->getbuzzer(),1000);
            m_hardwareobj->setPIRstatus(0);
          }
          else if(waitfacial==0) //if user is not detected
          {
            m_frobj->set_attempts(); //counting attempts 
          }
        }
      }else if(!m_hardwareobj->getPIRstatus()&&m_frobj->check_attempts()) //if PIR not detected
        {
          Serial.print('0');
          if(m_messobj->check_buffer())
          {
            waitfacial=Serial.read();
          };
        }
       else //if the ESP didn't pass the first two conditions
       {
          Serial.print('0');
          if(m_messobj->check_buffer())
          {
            waitfacial=Serial.read();
          };
       }
    }
    
    
    //order
    if(m_messobj->check_buffer()) //Menu depending on user command
    {
    char m_order=Serial.read();
    //Serial.print(m_order);
    switch(m_order)
    {
      case 's': //Activate Hardware
            if(m_messobj->check_buffer())
            {
              m_messagepin1=Serial.read(); // Reading first half of the PIN
            };
            if(m_messobj->check_buffer())
            {
              m_messagepin2=Serial.read(); // Reading second half of the PIN
            };
            if(m_messagepin2==(int)'B'||m_messagepin1==(int)'B')
            {
              Serial.print("Going Back to Homepage!"); // Going back to homepage
            }
            else if(m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2)) //Comparing the PIN to set PIN
            {
              //Activating the hardware
            m_hardwareobj->setbuzzerstatus(1);
            m_hardwareobj->setsystemstatus(1);
            m_hardwareobj->setPIRstatus(1);
            m_hardwareobj->setmagswitchstatus(1);
            m_hardwareobj->set_turnon_time(); //Recording the activation time to add time delay
            m_hardwareobj->green_led_arrays_on();
            m_keypadobj->clean_attempts(); // Clear PIN attemptes
            Serial.print("this is correct PIN");
            }
            else if(!m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2)) // If Wrong PIN
            {
            m_keypadobj->set_attempts(); //Record Attempts + 1
            Serial.print("Incorrect PIN!");
            }      
            break;
      case 'e': //Deactivate Hardware Command
          if(m_messobj->check_buffer())
            {
              m_messagepin1=Serial.read();
            };
            if(m_messobj->check_buffer())
            {
              m_messagepin2=Serial.read();
            };
          if(m_messagepin2==(int)'B'||m_messagepin1==(int)'B')
            {
              Serial.print("Going Back to Homepage!");
            }
          else if(m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            //Deactivating all Hardware
            m_hardwareobj->setbuzzerstatus(0);
            m_hardwareobj->setsystemstatus(0);
            m_hardwareobj->setPIRstatus(0);
            m_hardwareobj->setmagswitchstatus(0);
            m_hardwareobj->set_m_Solenoidstatus(0);
            m_hardwareobj->close_buzzer();
            m_hardwareobj->open_Solenoid();
            m_hardwareobj->green_led_arrays_off();
            //Serial.print(m_hardwareobj->getbuzzerstatus());
            //Serial.print(m_order);
            m_keypadobj->clean_attempts();
            Serial.print("System Deacivated");
          }else if(!m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            m_keypadobj->set_attempts();
            Serial.print("Incorrect PIN!");
          }   
          break;
       case 'c': //Change Password Command
          if(m_messobj->check_buffer())
            {
              m_messagepin1=Serial.read();
            };
            if(m_messobj->check_buffer())
            {
              m_messagepin2=Serial.read();
            };
          if(m_messagepin2==(int)'B'||m_messagepin1==(int)'B')
            {
              Serial.print("Going Back to Homepage!");
            }
          else if(m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2)) //
          {
            Serial.print("PIN recover page");
            if(m_messobj->check_buffer())
            {
              Serial.read();
            };
            Serial.print('1');
            if(m_messobj->check_buffer())
            {
              m_newmessagepin1=Serial.read();
            };
            if(m_messobj->check_buffer())
            {
              m_newmessagepin2=Serial.read();
            };
            m_keypadobj->clean_attempts();
            m_keypadobj->setm_pin(m_newmessagepin1,m_newmessagepin2);
            Serial.print("PIN Changed!");
          }else if(!m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            Serial.print("Change PIN:");
            if(m_messobj->check_buffer())
            {
              Serial.read();
            };
            Serial.print('0');
            m_keypadobj->set_attempts();
            Serial.print("Incorrect PIN!");
          }   
          break;
       case 'r': //Add Red LEDs command by the user
          if(m_messobj->check_buffer())
            {
              m_messagepin1=Serial.read();
            };
            if(m_messobj->check_buffer())
            {
              m_messagepin2=Serial.read();
            };
          if(m_messagepin2==(int)'B'||m_messagepin1==(int)'B')
            {
              Serial.print("Going Back to Homepage!");
            }
          else if(m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            m_keypadobj->clean_attempts();
            Serial.print("PIN Correct");
            int tem_pin=0;
            if(m_messobj->check_buffer())
            {
               tem_pin=Serial.read(); //LED pin number
            }
            m_hardwareobj->add_newredled(tem_pin);
            Serial.print("Red LED Added to System");
          }else if(!m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            m_keypadobj->set_attempts();
            Serial.print("Incorrect PIN!");
          }   
          break; 
       case 'g': //Add Green LEDs command by the user
          if(m_messobj->check_buffer())
            {
              m_messagepin1=Serial.read();
            };
            if(m_messobj->check_buffer())
            {
              m_messagepin2=Serial.read();
            };
          if(m_messagepin2==(int)'B'||m_messagepin1==(int)'B')
            {
              Serial.print("already back to home page");
            }
          else if(m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            m_keypadobj->clean_attempts();
            Serial.print("PIN Correct");
            int tem_pin=0;
            if(m_messobj->check_buffer())
            {
               tem_pin=Serial.read();
            }
            m_hardwareobj->add_newgreenled(tem_pin);
            Serial.print("successed added");
          }else if(!m_keypadobj->cmp_pin(m_messagepin1,m_messagepin2))
          {
            m_keypadobj->set_attempts();
            Serial.print("this is wrong PIN");
          }   
          break;
       case 'z': // Exiting Menu
          break;
    }  
    }
  }else if((!m_frobj->check_attempts())||(!m_keypadobj->check_attempts())) //If system was locked 
  {
    if(m_messobj->check_buffer())
    {
      Serial.read();
    }
    Serial.print('2');
    Serial.print("Attempts Exceeded! System Locked for 10 minutes..");
    //Deactivate Hardware:
    m_hardwareobj->setPIRstatus(0);
    /*m_hardwareobj->setbuzzerstatus(0);
    m_hardwareobj->setsystemstatus(0);
    m_hardwareobj->setPIRstatus(0);
    m_hardwareobj->setmagswitchstatus(0);*/
    if(m_messobj->check_buffer())
    {
      Serial.read();
    }
  }
  
  m_hardwareobj->Hardwarework(); 
}
