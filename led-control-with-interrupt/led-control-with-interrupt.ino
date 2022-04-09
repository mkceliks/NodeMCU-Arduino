#include "DHT.h"

#define DHTDATA 5 
#define DHTTYPE DHT22

#define LedRed 13
#define LedYellow 12
#define LedGreen 11
#define LedBlue 10

#define LEVELCrit 25
#define LEVELWarn 35
#define INTPin 2

bool intFlag = false;

long LoopTime = 0;

float h = 0;
float t = 0;

DHT dht(DHTDATA, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  
  pinMode(LedRed,OUTPUT);
  pinMode(LedYellow,OUTPUT);
  pinMode(LedGreen,OUTPUT);
  pinMode(LedBlue,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(INTPin), isr_, RISING);
  dht.begin();
}
void isr_(){
  intFlag = true;
}
void loop() {
    if(intFlag){
      intFlag = false;
      digitalWrite(LedBlue,!digitalRead(LedBlue));
      Serial.println("Dış Kesme Geldi");
      delay(1000);
      digitalWrite(LedBlue,!digitalRead(LedBlue));
      Serial.println("Dış Kesme Bitti");
    }
     ReadFromDHT();
 ChangeLedStatus();
}

void ReadFromDHT(){
  h = dht.readHumidity();
  t = dht.readTemperature();
  while(true){
     if (!isnan(h) || !isnan(t)){
     break;
  }else{
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.println(t);
}
void ChangeLedStatus(){
  digitalWrite(LedRed,LOW);
  digitalWrite(LedYellow,LOW);
  digitalWrite(LedGreen,LOW);
  
  if(t < 20){
    digitalWrite(LedRed,HIGH);
  }else if(t < 30){
    digitalWrite(LedYellow,HIGH);
  }else{
    digitalWrite(LedGreen,HIGH);
  }
}
