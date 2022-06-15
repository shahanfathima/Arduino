void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println("Home Automation");
pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, LOW); 

}

void loop() {
  // put your main code here, to run repeatedly:



char inChar = (char)Serial.read();

if(inChar=='a')
{//led on

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    
}

else if(inChar=='b')
{//led off

                        // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  
}


}
