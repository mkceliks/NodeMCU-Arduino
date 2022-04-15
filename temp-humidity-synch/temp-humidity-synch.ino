#include "DHT.h"// Kütüphane eklendi.
#define LedBlue 3 // Mavi Led'in pini.
#define LedWhite 2 // Beyaz Led'in pini.
#define LedRed 6 // Kırmızı Led'in pini.
#define button 5 // Buton'un pini.

int DHTPIN = 8;  // DHT sensörünün pini.
DHT dht(DHTPIN, DHT11); // DHT tanımlaması.
int buttonStat; // Buton tıklanmasını ölçmek için bir değişken oluşturuldu.

void setup() {
  
Serial.begin(9600);  // Seri haberleşme terminalı başlatıldı. (9600. port)
dht.begin();  //dht sensörü başlat
pinMode(LedBlue,OUTPUT); // Mavi led'in output olduğu bildirildi. 
pinMode(LedWhite,OUTPUT);// Beyaz led'in output olduğu bildirildi. 
pinMode(LedRed,OUTPUT);// Kırmızı led'in output olduğu bildirildi. 
pinMode(button,INPUT);// Buton'un input olduğu bildirildi. 

}

void loop() {
  
  buttonStat = digitalRead(button);// Buton'un anlık değeri okundu.
  if(buttonStat == 1 ){ // Buton'a basıldı ise..
    digitalWrite(LedRed,LOW); // Kırmızı led'i söndür.
    Serial.println("SICAKLIK ÖLÇÜLÜYOR....."); // Ekrana yazı yazacak.
    digitalWrite(LedBlue,HIGH); // Mavi led yanacak.
  digitalWrite(LedWhite,HIGH); // Beyaz led yanacak.
    delay(3000); // 3 saniye bekleyecek.
    float nem = dht.readHumidity();  // Nem ölçülecek.
  float sicaklik = dht.readTemperature();  // Sıcaklık ölçülecek.
  Serial.println(" HAVA DURUMU "); // Ekrana yazı yazacak.
  Serial.print(" Nem: % ");// Ekrana yazı yazacak.      
  Serial.println(nem  ); // Ölçülen nem değeri yazılacak.
  delay(500); // 0.5 saniye beklenecek.
  Serial.print(" Sıcaklık: "); // Ekrana yazı yazacak.
  Serial.print(sicaklik); // Ölçülen sıcaklık değeri ekrana yazılacak.
  Serial.println("°C"); // Ekrana yazı yazılacak.
  delay(500); // 0.5 saniye beklenecek.
  
  }else{ // Buton'a basılmamış ise...
    digitalWrite(LedRed,HIGH); // Kırmızı led yanacak.
    digitalWrite(LedBlue,LOW); // Mavi led sönecek.
    digitalWrite(LedWhite,LOW); // Beyaz led sönecek.
  }
  
}
