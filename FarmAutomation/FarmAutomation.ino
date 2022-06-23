// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
// include the library code:
#include <LiquidCrystal.h>
bool LED_STATE = true;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int timecount=0,dispcount=0;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  
    int relay=3;

    int hr1,hr2,hr3,mn1,mn2,mn3,timedelay;
    int runflag=0;
    
    int delayhr=0;
    int delaymn=45;

    
    int dispint=10;
void setup () {

pinMode(LED_BUILTIN, OUTPUT);
    pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);  

     lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Farm Automation");
  
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(57600);
 // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));


  }


hr1=10;
hr2=15;
hr3=15;

mn1=00;
mn2=30;
mn3=30;

  delay(3000);


  cli();                      //stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
 
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */  
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  
  /*3. We enable compare match mode on register A*/
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A 
  
  /*4. Set the value of register A to 31250*/
  OCR1A = 31250;             //Finally we set compare register A to this value  
  sei();      

  
lcd.clear();
}

void loop () {
    DateTime now = rtc.now();
    
//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();


    Serial.print("timecount  - ");
  Serial.print(timecount);
   Serial.print("  Dispcount  - ");
  Serial.println(dispcount);

if(dispcount==0)
{
  Serial.println("Time display");
  lcd.setCursor(0, 0);
  lcd.print("Date:");
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);   
  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  }

  else if(dispcount==1)
  {

     Serial.println("Status Display");
      Serial.print("runflag- ");
       Serial.println(runflag);
     lcd.setCursor(0, 0);
     lcd.print("Irrigation");
     if(runflag==0)
     {
      lcd.setCursor(0, 1);
      lcd.print("Status: OFF");
     }
     else
     {
      lcd.setCursor(0, 1);
      lcd.print("Status: ON");
     }
     
  }

  else if(dispcount==2)
  {

    
     lcd.setCursor(0, 0);
     lcd.print("Irrigation");
     lcd.setCursor(0, 1);
     lcd.print("Interval - ");

lcd.print(delayhr);
lcd.print(":");
lcd.print(delaymn);   
     
  }

  else if(dispcount==3)
  {

    
     lcd.setCursor(0, 0);
     lcd.print(" ON Time");
     lcd.setCursor(0, 1);
     lcd.print(hr1);
     lcd.print(":");
     lcd.print(mn1);
     lcd.print(",");

       lcd.print(hr2);
     lcd.print(":");
     lcd.print(mn2);
     lcd.print(",");

       lcd.print(hr3);
     lcd.print(":");
     lcd.print(mn3);
    

     
  }


    if((((now.hour()==hr1)&&(now.minute()==mn1))||  ((now.hour()==hr2)&&(now.minute()==mn2))|| ((now.hour()==hr3)&&(now.minute()==mn3))) && (runflag==0))
    
    
    {
      Serial.print("motor on");

      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(relay, LOW);   // turn the LED on (HIGH is the voltage level)
   runflag=1;
   
    }

    
if((((now.hour()==hr1+delayhr)&&(now.minute()==mn1+delaymn))||  ((now.hour()==hr2+delayhr)&&(now.minute()==mn2+delaymn))|| ((now.hour()==hr3+delayhr)&&(now.minute()==mn3+delaymn))) && (runflag==1))
    {
                             // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   digitalWrite(relay, HIGH);    // turn the LED off by making the voltage LOW
   Serial.print("motor off");
    runflag=0;
    }

    delay(1000);
  lcd.clear();
   
}


ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt

  timecount++;

  

  if( timecount>=dispint)
  {
    timecount=0;
 dispcount++;



 if( dispcount>=4)
 {
  dispcount=0;
 }
 }

  
  }
