int led1=12; //D5Connect the short leg of the LED (the negative leg, called the cathode) to the GND
int led2=13;//D6
int led3=14;//D7
int sensor=A0;
int temp;
int Status = 4;  // Digital pin D2 ie the led positive
int sensor1 = 5;  // Digital pin D1 the middle pin ie the output of the sensor

void setup()
{ pinMode(12,OUTPUT) ;
  pinMode(13,OUTPUT) ;
  pinMode(14,OUTPUT) ;
  pinMode(A0,INPUT) ;
  pinMode(sensor1, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output
}
  void loop()
 {  temp=readTemp() ;
    if((temp>=20)&&(temp<25))
    {
  digitalWrite(led1, HIGH);
  digitalWrite(led2,LOW) ;
  digitalWrite(led3,LOW) ;
  delay(5000);
    }
else if((temp>=25)&&(temp<30))
{
  digitalWrite(led2,HIGH) ;
  digitalWrite(led1,LOW) ;
  digitalWrite(led3,LOW) ;
  delay(5000);
}
 else if(temp>30)
 {
  digitalWrite(led3,HIGH) ;
  digitalWrite(led1,LOW) ;
  digitalWrite(led2,LOW) ;
  delay(5000);
 }


 long state = digitalRead(sensor1);
    if(state == HIGH) {
      digitalWrite (Status, HIGH);
      //Serial.println("Motion detected!");
      //delay(1000);
    }
    else {
      digitalWrite (Status, LOW);
      //Serial.println("Motion absent!");
     // delay(1000);
      }

 
}
  int readTemp()
 { temp=analogRead(sensor) ;
return temp*0.48828125;
}
