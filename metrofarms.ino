#include "DHT.h"

#define DHTPIN 6   
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
#define led 3
const int trigPin=10;
const int echoPin=9;
#define ledgrowth 10
long duration;
int distance;
#include <Servo.h>

Servo myservo;
int pos=0;
void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(led,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  dht.begin();
  myservo.attach(11);
}

void loop() {
  
  delay(2000);

  
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();
 
  float f = dht.readTemperature(true);

  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  
  float hif = dht.computeHeatIndex(f, h);
  
  float hic = dht.computeHeatIndex(t, h, false);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.017;

  Serial.print("Distance:");
  Serial.println(distance);
  if((h>=68.0&&h<=72.0)&&(t>=22.0&&t<=30.0)) //optimum condition 
  {
    digitalWrite(led,LOW);
    
  }
  else
  {
    
    digitalWrite(led,HIGH);
    delay(200);
    digitalWrite(led,LOW);
    delay(100);
  }
  
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
