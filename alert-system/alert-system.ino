#include "DHT.h"  
int DHTPIN = 8;  
DHT dht(DHTPIN, DHT11);  // dht adında sensör nesnesi tanımla. 
#define LedRed 5
#define LedYellow 9
#define LedGreen 3
#define potPin A0
int potDegeri = 0;
int mapValue = 0;
void setup() {
  Serial.begin(9600);  
  dht.begin();  //dht sensörü başlat
  pinMode(LedGreen,OUTPUT);
  pinMode(LedYellow,OUTPUT);
  pinMode(LedRed,OUTPUT);
  pinMode(potPin,INPUT);
  
}

void loop() {
  float nem = dht.readHumidity(); 
  float sicaklik = dht.readTemperature();  
  Serial.print("Nem: Yüzde ");      
  Serial.print(nem  );
  Serial.print(" Sıcaklık: ");
  Serial.print(sicaklik);
  Serial.print(" C");
  mapValue = analogRead(potPin);
  potDegeri=map(mapValue,0,1023,0,255);
  Serial.print(" POTANSİYEL METRE: ");
  Serial.println(potDegeri);
    if(nem >= 70){
    analogWrite(LedRed,potDegeri);
    digitalWrite(LedYellow,LOW);
    digitalWrite(LedGreen,LOW);
    delay(100);
    digitalWrite(LedRed,LOW);
    delay(100);
  }
  else if(nem >= 65){
    analogWrite(LedRed,potDegeri);
    digitalWrite(LedYellow,LOW);
    digitalWrite(LedGreen,LOW);
    delay(400);
    digitalWrite(LedRed,LOW);
    delay(300);
  }
  else if(nem >=60){
    analogWrite(LedRed,potDegeri);
    digitalWrite(LedYellow,LOW);
    digitalWrite(LedGreen,LOW);
    delay(700);
    digitalWrite(LedRed,LOW);
    delay(300);
  }
else{
    analogWrite(LedGreen,potDegeri);
    digitalWrite(LedYellow,LOW);
    digitalWrite(LedRed,LOW);
  }
}
