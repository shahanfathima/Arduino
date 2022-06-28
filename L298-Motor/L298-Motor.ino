
// the setup function runs once when you press reset or power the board

int l298_1_in1=9;
int l298_1_in2=10;

int l298_1_in3=11;
int l298_1_in4=12;

int l298_2_in1=1;
int l298_2_in2=2;



void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(l298_1_in1, OUTPUT);
  pinMode(l298_1_in2, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
            motor1clock();
            delay(3000);
            motor1anticlock();
            delay(3000);
            motor1stop();
            delay(3000);
                      
}


void motor1clock()
{

  digitalWrite(l298_1_in1, HIGH);   
digitalWrite(l298_1_in2, LOW); 
}

void motor1anticlock()
{

  digitalWrite(l298_1_in1, LOW);   
digitalWrite(l298_1_in2, HIGH); 
}


void motor1stop()
{

  digitalWrite(l298_1_in1, LOW);   
digitalWrite(l298_1_in2,LOW); 
}
