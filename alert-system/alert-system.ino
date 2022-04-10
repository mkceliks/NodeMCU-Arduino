#include "DHT.h"  
int DHTPIN = 8;  
DHT dht(DHTPIN, DHT11);  // dht adında sensör nesnesi tanımla. 
#define LedRed 5
#define LedYellow 9
#define LedGreen 3
#define potPin A0
#define button 2
int potDegeri = 0;
int mapValue = 0;
int buttonStatus = 0;
void setup() {
  Serial.begin(9600);  
  dht.begin();  //dht sensörü başlat
  pinMode(LedGreen,OUTPUT);
  pinMode(LedYellow,OUTPUT);
  pinMode(LedRed,OUTPUT);
  pinMode(potPin,INPUT);
  pinMode(button,INPUT);
  
}

void loop() {
  
  float nem = dht.readHumidity(); 
  float sicaklik = dht.readTemperature(); 
  Serial.println(" HAVA DURUMU ");
  Serial.print(" Nem: % ");      
  Serial.println(nem  );
  Serial.print(" Sıcaklık: ");
  Serial.print(sicaklik);
  Serial.println("°C");
  
  mapValue = analogRead(potPin);
  potDegeri=map(mapValue,0,1023,0,255);
  Serial.print(" POTANSİYEL METRE: ");
  Serial.println(potDegeri);
  
  buttonStatus = digitalRead(button);
  Serial.println(" Alarm Buton = DEAKTİF");
  Serial.println("*************************************************");
     if(buttonStatus == 1){
      Serial.println("ALARMA BASILDI!!!!!!");
      delay(2000);
      while(nem > 60){
      Serial.println("İŞLEM KONTROL ALTINA ALINIYOR...");
      delay(2000);
      float nem = dht.readHumidity(); 
      Serial.print("Anlık Nem: Yüzde ");      
      Serial.println(nem);
      if(nem < 60){
        break;
      }
      analogWrite(LedYellow,potDegeri);
      digitalWrite(LedRed,LOW);
      digitalWrite(LedGreen,LOW);
      }
      Serial.println("İŞLEM KONTROL ALTINA BAŞARIYLA ALINDI... ");
      delay(2000);
      buttonStatus = 0;
  }
    nem = dht.readHumidity(); 
    if(nem >= 70){
    Serial.println("ÇOK TEHLİKELİ SEVİYEDE!!!!!!");
    delay(500);
    analogWrite(LedRed,potDegeri);
    digitalWrite(LedYellow,LOW);
    digitalWrite(LedGreen,LOW);
    delay(100);
    digitalWrite(LedRed,LOW);
    delay(100);
  }
  else if(nem >= 65){
    Serial.println("TEHLİKELİ SEVİYEDE!!!!!!");
    analogWrite(LedRed,potDegeri);
    digitalWrite(LedYellow,LOW);
    digitalWrite(LedGreen,LOW);
    delay(400);
    digitalWrite(LedRed,LOW);
    delay(300);
  }
  else if(nem >60){
    Serial.println("TEHLİKELİ OLABİLİR!!!!!!");
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
    delay(3000);
  }
  
  }
    
