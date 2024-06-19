//Project_04
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <WiFi.h>
#include <WebServer.h>

// Глобални променливи за HTTP сървъра
WebServer httpServer(80);
extern int counter;

// Деклариране на глобалните променливи за температурите
// extern int temp1;
// extern int temp2;
// extern int temp3;

void handleRoot() {
  // int temp1 = randomTemperature();
  // int temp2 = randomTemperature();
  // int temp3 = randomTemperature();

  // Добавяне на уникален параметър към URL-то на иконката
  String imageUrl = "https://batevesko.github.io/redutaBig04.png?v=" + String(millis());

  String content = "<!DOCTYPE html>";
  content += "<html lang='en'>";
  content += "<head>";
  content += "<meta charset='UTF-8'>";
  content += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  content += "<title>Hello, Bate Vesko!!!</title>";
  content += "<style>";
  content += "body { display: flex; flex-direction: column; align-items: center; justify-content: center; width: 100%; max-width: 1600px; height: 90vh; margin: auto,auto; border: 2px solid blue; background-color: rgb(250, 250, 0);}";
  content += ".container { position: relative; width: 100%; max-width: 1000px; height: auto; border: 2px solid red; background-color: rgb(250, 166, 56); }";
  content += ".image-container { position: relative; width: 100%; padding-bottom: 67.6%; }"; // Съотношение на иконката
  content += ".fullscreen-img { position: absolute; top: 0; left: 0; width: 100%; height: 100%; object-fit: contain; }"; // Ограничете височината на иконката и запазете съотношението
  content += ".temperature { position: absolute; background: yellow; color: red; border: 2px solid blue; border-radius: 10px; width: 60px; height: 30px; display: flex; justify-content: center; align-items: center; font-size: 24px; }";
  content += "#temp1 { top: 27%; left: 22%; }"; // Относителни позиции спрямо изображението
  content += "#temp2 { top: 13%; left: 79%; }";
  content += "#temp3 { top: 65%; left: 75%; }";
  content += "h1 { margin-top: 50px; }"; // Отстояние от горния край
  content += "h2 { margin-bottom: 50px; }"; // Отстояние от долния край
  content += "</style>";
  content += "</head>";
  content += "<body>";
  content += "<h1>Hello, Bate Vesko!!!</h1>";
  content += "<div class='container'>";
  content += "<div class='image-container'>";
  content += "<img src='" + imageUrl + "' alt='Reduta Icon' class='fullscreen-img'>";
  content += "<div class='temperature' id='temp1'>" + String(temp1) + "&#176;C" + "</div>";
  content += "<div class='temperature' id='temp2'>" + String(temp2) + "&#176;C" + "</div>";
  content += "<div class='temperature' id='temp3'>" + String(temp3) + "&#176;C" + "</div>";
  content += "</div>";
  content += "</div>";
  content += "<h2>Free heap: " + String(ESP.getFreeHeap()) + " Counter: " + String(counter) + "</h2>";
  content += "</body>";
  content += "</html>";

  httpServer.send(200, "text/html", content);
}

void initWiFiAndServer() {
  // const char *ssid = "TP-Link_1AEA";
  // const char *password = "83590566";

  const char *ssid = "A1_6531";
  const char *password = "48575443BD107EA3";

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  httpServer.on("/", handleRoot);
  httpServer.begin();
  Serial.println("HTTP server started");
}

#endif // HTTPSERVER_H
