#define BLYNK_TEMPLATE_ID "TMPL3wlMBSt6v"
#define BLYNK_TEMPLATE_NAME "SyringPump"
#define BLYNK_AUTH_TOKEN "cSb1Go_3a6CsFuJnmzx-DMTocfYIv6kR"

#define BLYNK_PRINT Serial




#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "Galaxy S22 Ultra 95A4";
char pass[] = "sadri123";

int power_state=0;
int flow_rate=0;



int step=9;
int dir=8;
int flag=0;

int del=0;

void stepper_high(int d)
{digitalWrite(dir,HIGH);
if (power_state==1){
  for(int i=0;i<=10000;i++){
digitalWrite(step,HIGH);
delayMicroseconds(d);
digitalWrite(step,LOW);
delayMicroseconds(d);
Serial.println(d);
Blynk.run();
  }}
}

void stepper_low(int d)
{digitalWrite(dir,LOW);
if(power_state==1){
  for(int i=0;i<=10000;i++){
digitalWrite(step,HIGH);
delayMicroseconds(d);
digitalWrite(step,LOW);
delayMicroseconds(d);
Serial.println(d);
Blynk.run();
  }}
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); 
  // String i = param.asStr();
  // double d = param.asDouble();
  // Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
  power_state=pinValue;

}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); 
 if(pinValue!=flow_rate)
 {flag=1;
flow_rate=pinValue;
Serial.println("Value changed");
 }
  if(flow_rate!=0)
 { del=600-(50*pinValue);
power_state=1;
 }
  else
  power_state=0;
  
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); 
  // String i = param.asStr();
  // double d = param.asDouble();
  // Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
  stepper_high(100);
  

}
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); 
  // String i = param.asStr();
  // double d = param.asDouble();
  // Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
    stepper_low(100);

  Serial.println("End");  

}

void setup()
{Serial.begin(115200);
pinMode(step,OUTPUT);
pinMode(dir,OUTPUT);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);

}

void loop()
{
  Blynk.run();
  if(power_state==1)
   { digitalWrite(step,HIGH);
     delayMicroseconds(del);
     digitalWrite(step,LOW);
     delayMicroseconds(del);
     Serial.println(del);
    //stepper(del);
    Blynk.run();
  }
 //Serial.println("OK");
}