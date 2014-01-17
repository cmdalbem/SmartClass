int ENA=5;//connected to Arduino's port 5(output pwm)
int IN1=2;//connected to Arduino's port 2
int IN2=3;//connected to Arduino's port 3
int ENB=6;//connected to Arduino's port 6(output pwm)
int IN3=4;//connected to Arduino's port 4
int IN4=7;//connected to Arduino's port 7


int first;
int second;
int third;
int fourth;

int inByte = 0; 
int valFade1=0;
int valFade2=0;
int time=0;
int val=0;


void setup()
{
	Serial.begin(9600);  //inizializzo la seriale
	pinMode(ENA,OUTPUT);//output
	pinMode(ENB,OUTPUT);
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);
	digitalWrite(ENA,LOW);
	digitalWrite(ENB,LOW);//stop driving
	digitalWrite(IN1,LOW); 
	digitalWrite(IN2,HIGH);//setting motorA's directon
	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);//setting motorB's directon
}


void loop()
{
	first=0;
	second=0;
	third=0;
	fourth=0;
	inByte = 0; 

	val=0;
	// if we get a valid byte, read analog ins:
	//taking value for Rouge
	if (Serial.available() > 5) {
		// get incoming byte:
		first = Serial.read();
		second = Serial.read();
		third = Serial.read();
		fourth = Serial.read();

		// volet1;
		Serial.println("v");
		Serial.println(first);
		Serial.println("l");
		Serial.println(second);
		Serial.println("1");
		Serial.println(third);
		Serial.println(":");
		Serial.println(fourth);

		if (first == 'v' && second == 'l' && third == '1' && fourth == ':') {
			Serial.println("enter in vl1");
			inByte = Serial.read();
			val=0;
			while (inByte != ':') {
				// while we are reading the first serial value
				val= val*10 + inByte - '0';
				inByte = Serial.read(); 
				Serial.println("val while");
				Serial.println(val);
			}
			Serial.println("valFade1vecchio");   
			Serial.println(valFade1);
			Serial.println("VAL");   
			Serial.println(val);
			if(val>valFade1 && valFade1<=100 &&valFade1>=0 && val>=0 && val<=100){

				Serial.println("time:\n");
				time=val-valFade1;
				Serial.println(time);
				Serial.println("valFade1:\n");
				valFade1+=time;
				Serial.println(valFade1);
				Serial.println("open volet1\n");
				digitalWrite(IN1,LOW); 
				digitalWrite(IN2,HIGH);//setting motorA's directon
				time = map(time, 0, 100, 0, 13000);     
				Serial.println("tempo 0-3000:");
				Serial.println(time);
				analogWrite(ENA,255);//start driving motorA
				delay(time);
				analogWrite(ENA,0);//start driving motorA
			}
			/////
			else if(val<valFade1 && valFade1<=100 &&valFade1>=0 && val>=0 && val<=100){

				Serial.println("time:\n");
				time=valFade1-val;
				Serial.println(time);
				Serial.println("valFade1:\n");
				valFade1-=time;
				Serial.println(valFade1);
				Serial.println("close volet1\n");
				digitalWrite(IN1,HIGH); 
				digitalWrite(IN2,LOW);//setting motorA's directon
				time = map(time, 0, 100, 0, 13000);     
				Serial.println("tempo 0-3000:");
				Serial.println(time);
				analogWrite(ENA,255);//start driving motorA
				delay(time);
				analogWrite(ENA,0);//start driving motorA
			}
			else{ 
				Serial.println("impossible command\n");
			}

		}
		else if (first == 'v' && second == 'l' && third == '2' && fourth == ':') {
			Serial.println("enter in vl2");
			inByte = Serial.read();
			val=0;
			while (inByte != ':') {
				// while we are reading the first serial value
				val= val*10 + inByte - '0';
				inByte = Serial.read(); 
				Serial.println("val while");
				Serial.println(val);
			}
			Serial.println("valFade1vecchio");   
			Serial.println(valFade2);
			Serial.println("VAL");   
			Serial.println(val);
			if(val>valFade2 && valFade2<=100 &&valFade2>=0 && val>=0 && val<=100){

				Serial.println("time:\n");
				time=val-valFade2;
				Serial.println(time);
				Serial.println("valFade2:\n");
				valFade2+=time;
				Serial.println(valFade2);
				Serial.println("open volet1\n");
				digitalWrite(IN3,LOW); 
				digitalWrite(IN4,HIGH);//setting motorA's directon
				time = map(time, 0, 100, 0, 13000);     
				Serial.println("tempo 0-3000:");
				Serial.println(time);
				analogWrite(ENB,255);//start driving motorA
				delay(time);
				analogWrite(ENB,0);//start driving motorA
			}
			/////
			else if(val<valFade2 && valFade2<=100 &&valFade2>=0 && val>=0 && val<=100){

				Serial.println("time:\n");
				time=valFade2-val;
				Serial.println(time);
				Serial.println("valFade2:\n");
				valFade2-=time;
				Serial.println(valFade2);
				Serial.println("close volet2\n");
				digitalWrite(IN3,HIGH); 
				digitalWrite(IN4,LOW);//setting motorA's directon
				time = map(time, 0, 100, 0, 13000);     
				Serial.println("tempo 0-3000:");
				Serial.println(time);
				analogWrite(ENB,255);//start driving motorA
				delay(time);
				analogWrite(ENB,0);//start driving motorA
			}
			else{ 
				Serial.println("impossible command\n");
			}

		}
	}
}





