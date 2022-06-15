
//https://www.youtube.com/watch?v=CZVOp4oVfBk
//https://www.youtube.com/watch?v=a0gIC27nBlE
// the setup function runs once when you press reset or power the board

int relay=2;

 int en1=13;
 int en2=12;



 
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(relay, OUTPUT);
   pinMode(en1, OUTPUT);
      pinMode(en2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(relay, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
         
  
 
  digitalWrite(en1, HIGH);
digitalWrite(en2, LOW);

delay(5000);
digitalWrite(en1, LOW);
digitalWrite(en2, LOW);

digitalWrite(en1, LOW);
digitalWrite(en2, HIGH);
delay(5000);
digitalWrite(en1, LOW);
digitalWrite(en2, LOW);


digitalWrite(relay, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
}
