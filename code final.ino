#include <dht.h>
dht DHT;
#define DHT11_PIN 2  //// connect to d4 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "NodeMCU";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

uint8_t LED1pin = 12;
bool LED1status = LOW;

uint8_t LED2pin = 13;
bool LED2status = LOW;

uint8_t LED3pin = 15;
bool LED3status = LOW;
int led1=12; //D5Connect the short leg of the LED (the negative leg, called the cathode) to the GND
int led2=13;//D6
int led3=14;//D7
int temp,hum;
int Status = 4;  // Digital pin D2 ie the led positive
int sensor1 = 5;  // Digital pin D1 the middle pin ie the output of the PIR sensor


void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
   server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();

  if(LED3status){
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}
   if(LED3status)
  {digitalWrite(LED3pin, HIGH);}
  else
  {digitalWrite(LED3pin, LOW);}
  long state = digitalRead(sensor1);
    if(state == HIGH) {
      digitalWrite (Status, LOW);
      //Serial.println("Motion detected!");
     delay(1000);
    }
    else {
      digitalWrite (Status, HIGH);
      //Serial.println("Motion absent!");
     delay(1000);
      } 
}

else{
    // put your main code here, to run repeatedly:
int chk = DHT.read11(DHT11_PIN);
  //temp= DHT.temperature;
  temp=DHT.humidity;
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Serial.print("temp ");
  Serial.println(temp);
  delay(1000);
  

  if((temp>=70)&&(temp<75))
    {
  digitalWrite(led1, LOW);
  digitalWrite(led2,HIGH) ;
  digitalWrite(led3,HIGH) ;
 // delay(5000);
    }
else if((temp>=75)&&(temp<80))
{
  digitalWrite(led2,LOW) ;
  digitalWrite(led1,HIGH) ;
  digitalWrite(led3,HIGH) ;
 // delay(5000);
}
 else if(temp>80)
 { 
  digitalWrite(led1, LOW);
  digitalWrite(led2,HIGH) ;
  digitalWrite(led3,HIGH) ;
 
 // delay(5000);
 }
}
}
void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  LED3status = LOW;
  
  Serial.println("led1 Status: OFF | led2 Status: OFF |led3 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status)); 
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("led1 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("led1 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("led2 status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true,LED3status)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("led2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false,LED3status)); 
}


void handle_led3on() {
  LED3status = HIGH;
  Serial.println("led3 status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,true)); 
}

void handle_led3off() {
  LED3status = LOW;
  Serial.println("led3 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,false)); 
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
  long state = digitalRead(sensor1);
    if(state == HIGH) {
      digitalWrite (Status, LOW);
      //Serial.println("Motion detected!");
     delay(1000);
    }
    else {
      digitalWrite (Status, HIGH);
      //Serial.println("Motion absent!");
     delay(1000);
      } 
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>SMART ROOM</h1>\n";
  ptr +="<h3>Fan Speed Control</h3>\n";
  
   if(led1stat)
  {ptr +="<p>L1 Status: OFF</p><a class=\"button button-off\" href=\"/led1off\">ON</a>\n";}
  else
  {ptr +="<p>L1 Status: ON</p><a class=\"button button-on\" href=\"/led1on\">OFF</a>\n";}

  if(led2stat)
  {ptr +="<p>L2 Status: OFF</p><a class=\"button button-off\" href=\"/led2off\">ON</a>\n";}
  else
  {ptr +="<p>L2 Status: ON</p><a class=\"button button-on\" href=\"/led2on\">OFF</a>\n";}
  ptr +="<h3>MANUAL SELECTION</h3>\n";
   if(led3stat)
  {ptr +="<p>manual: ON</p><a class=\"button button-off\" href=\"/led3off\">OFF</a>\n";}
  else
  {ptr +="<p>manual: OFF</p><a class=\"button button-on\" href=\"/led3on\">ON</a>\n";}
  ptr +="<h3>HIGH   L1 ON, L2 ON </h3>\n";
  ptr +="<h3>MEDUIM L1 OFF L2 ON</h3>\n";
  ptr +="<h3>LOW    L1 ON  L2 OFF</h3>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
