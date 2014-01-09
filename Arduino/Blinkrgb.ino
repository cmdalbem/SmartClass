/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int r= 12;
int g = 11;
int b = 10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(r, OUTPUT);     
  pinMode(g, OUTPUT);  
   pinMode(b, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(r, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  delay(1000);               // wait for a second
  digitalWrite(r, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  delay(1000);               // wait for a second
}
