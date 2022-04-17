#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT11

const char* ssid = "Network kullanıcı adı";  
const char* password = "Network Şifresi";  

ESP8266WebServer server(80);

uint8_t DHTPin = 4; // DHT Pin Tanımlaması
               
DHT dht(DHTPin, DHTTYPE);  // DHT tanımlaması.              

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Bağlanıyor  ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); // WiFi başlat.

  while (WiFi.status() != WL_CONNECTED) {// WiFi bağlantı kontrolü sağlanıyor.
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi başarıyla bağlandı.");
  Serial.print("IP:  ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server başlatıldı.");

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {

 float Temperature = dht.readTemperature(); // Sıcaklık Değeri Alınıyor.
 float Humidity = dht.readHumidity(); // Nem Değeri Alınıyor.
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Bulunamadı.");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"    <title>Document</title>\n"
"    \n"
"    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">\n"
"    <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p\" crossorigin=\"anonymous\"></script>\n"
"    <meta name=\"theme-color\" content=\"#7952b3\">\n"
"\n"
"\n"
"    <style>\n"
"      .bd-placeholder-img {\n"
"        font-size: 1.125rem;\n"
"        text-anchor: middle;\n"
"        -webkit-user-select: none;\n"
"        -moz-user-select: none;\n"
"        user-select: none;\n"
"      }\n"
"\n"
"      @media (min-width: 768px) {\n"
"        .bd-placeholder-img-lg {\n"
"          font-size: 3.5rem;\n"
"        }\n"
"      }\n"
"      body {\n"
"  background-image: linear-gradient(180deg, #eee, #fff 100px, #fff);\n"
"}\n"
"\n"
".container {\n"
"  max-width: 960px;\n"
"}\n"
"\n"
".pricing-header {\n"
"  max-width: 700px;\n"
"}\n"
"    </style>\n"
"\n"
"<header>\n"
"\n"
"    <div class=\"pricing-header p-3 pb-md-4 mx-auto text-center\">\n"
"      <h1 class=\"display-4 fw-normal\">Hava Durumu</h1>\n"
"      <p class=\"fs-5 text-muted\">Node MCU ile geliştirilmiş bir hava durumu ölçme ve web üzerinde gösterme gerçekleşen yazılıma hoş geldiniz...</p>\n"
"    </div>\n"
"  </header>\n"
"</head>\n"
"<body>\n"
"    \n"
"    <div style=\"margin:auto;\" class=\"row text-center\">\n"
"        <div class=\"col-md-6\">\n"
"          <div class=\"card mb-4 rounded-3 shadow-sm\">\n"
"            <div class=\"card-header py-3\">\n"
"              <h4 class=\"my-0 fw-normal\">SICAKLIK</h4>\n"
"            </div>\n"
"            <div class=\"card-body\">\n"
"              <h1 class=\"card-title pricing-card-title\">";
ptr += (int)Temperaturestat;
ptr += "<small class=\"text-muted fw-light\">°C</small></h1>\n"
"            </div>\n"
"          </div>\n"
"        </div>\n"
"        <div class=\"col-md-6\">\n"
"          <div class=\"card mb-4 rounded-3 shadow-sm\">\n"
"            <div class=\"card-header py-3\">\n"
"              <h4 class=\"my-0 fw-normal\">Nem</h4>\n"
"            </div>\n"
"            <div class=\"card-body\">\n"
"              <h1 class=\"card-title pricing-card-title\">";
ptr += (int)Humiditystat;
ptr += "<small class=\"text-muted fw-light\">%</small></h1>\n"
"            </div>\n"
"          </div>\n"
"        </div>\n"
"\n"
"      </div>\n"
"</body>\n"
"</html>";
  return ptr;
}
