// Luca Rizzo

//Kevin Grandmage

#define Rouge 11        // LED rouge
#define Vert 10        // LED vert
#define Bleu 9
#define Blanc 6

int BleuPow=0;
int VertPow=0; //power
int RougePow=0;
int lum = 0;
int inByte = 0; 
int val=0;
int valFade = 0; 

int first=0;
int second=0;
int third=0;
int fourth=0;
// incoming serial byte 
void setup() {  
  Serial.begin(9600);  //inizializzo la seriale
  pinMode(Rouge, OUTPUT);
  pinMode(Vert, OUTPUT);     //dichiaro i pin del primo LED RGB come uscita
  pinMode(Bleu, OUTPUT);
  pinMode(Blanc, OUTPUT);
}  

void loop()
{
  // Reinit the value to 0
  RougePow = 0;
  VertPow = 0;
  BleuPow = 0;
  val=0;
  // if we get a valid byte, read analog ins:
  //taking value for Rouge
  if (Serial.available() > 0) {
    // get incoming byte:
    first = Serial.read();
    second = Serial.read();
    third = Serial.read();
    fourth = Serial.read();

    // manual
    if (first == 'm' && second == 'm' && third == 'm' && fourth == ':') {
      inByte = Serial.read();
      while (inByte != ':') {
        // while we are reading the first serial value
        val= val*10 + inByte - '0';
        inByte = Serial.read(); 
      }
      int mapped_val = map(val, 0, 1024, 0, 255);
      Serial.println(mapped_val);
      Serial.println("VAL");
      Serial.println(val);
      valFade = mapped_val;
      analogWrite(Blanc, valFade);
    }
    
    // white 
    else if (first == 'w' && second == 'w' && third == 'w' && fourth == ':') {
      inByte= Serial.read();
      while (inByte != ':') {
        // while we are reading the first serial value
        val= val*10 + inByte - '0';
        inByte = Serial.read(); 
      }

      int mapped_val = map(val, 0, 1024, 0, 255);
      if(val >= 320) { //turn on
       
        if(mapped_val>valFade+20){	

          for(;valFade<mapped_val;valFade++){
            analogWrite(Blanc, valFade);  
            delay(10);
          }


        } else if ( mapped_val < valFade - 20 ) {
          for(; valFade > mapped_val; valFade--) {
          analogWrite(Blanc, valFade);  
          delay(10);
          }
        }
      } else { //turn off
        while ( valFade>0 ) {
          valFade--;
          analogWrite(Blanc, valFade);  
          delay(10);
        }
      }    
    }




    else if (first == 'r' && second == 'g' && third == 'b' && fourth == ':') {

      inByte = Serial.read();
      while (inByte != ':') {
        // while we are reading the first serial value
        RougePow = RougePow*10 + inByte - '0';
        inByte = Serial.read();
      }
      // flush the :
      inByte = Serial.read(); 
      while (inByte != ':') {
        VertPow = VertPow*10 + inByte - '0';
        inByte = Serial.read();
      }
      // flush the :
      inByte = Serial.read(); 
      while (inByte != ':') {
        BleuPow = BleuPow*10 + inByte - '0';
        inByte = Serial.read();
      }
      analogWrite( Rouge, RougePow);
      analogWrite( Vert, VertPow); 
      analogWrite( Bleu, BleuPow);
      Serial.print(RougePow);
      Serial.print(":");
      Serial.print(VertPow);
      Serial.print(":");
      Serial.print(BleuPow);
      Serial.print(":\n");
    }
  }
  //digitalWrite(LED, HIGH);  // turn on the  LED 
  delay(500);
}



