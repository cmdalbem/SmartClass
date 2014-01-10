#define photor A0  //on define le pin où on attache le capteur de luminositè
void setup()  {  
  pinMode(A0,INPUT);   
  Serial.begin(9600); // begin serial communication
}   
void loop()  
{  
  int val = analogRead(photor); 
  Serial.print("lum:");
  Serial.print(val,DEC);
  Serial.println(":");
  delay(1000);
}  

