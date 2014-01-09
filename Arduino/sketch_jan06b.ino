// Luca Rizzo
//Kevin Grandmage
  
  #define Rouge 12         // LED rouge
  #define Vert 11        // LED vert
  #define Bleu 10
  
int BleuPow=0;
int VertPow=0; //power
int RougePow=0;
int inByte = 0;         // incoming serial byte 
void setup() {  
 Serial.begin(9600);  //inizializzo la seriale


  pinMode(Rouge, OUTPUT);
  pinMode(Vert, OUTPUT);     //dichiaro i pin del primo LED RGB come uscita
  pinMode(Bleu, OUTPUT);
}  
  
void loop()
{

  // if we get a valid byte, read analog ins:
  //taking value for Rouge
  if (Serial.available() > 0) {
    // get incoming byte:
    while (inByte != ':') {
      RougePow = RougePow*10 + Serial.read() - '0';
    }
    while (inByte != ':') {
      RougePow = RougePow*10 + Serial.read() - '0';
    }
    while (inByte != ':') {
      RougePow = RougePow*10 + Serial.read() - '0';
    }
  }
  
  //digitalWrite(LED, HIGH);  // turn on the  LED 
 analogWrite( Rouge, RougePow);
 analogWrite( Vert, VertPow); 
 analogWrite( Bleu, BleuPow);
 Serial.print(RougePow);
 Serial.print(VertPow);
 Serial.print(BleuPow);
 delay(1000);
 }


