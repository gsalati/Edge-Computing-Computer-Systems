#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "GSALATI_NOTE";
const char* password = "Fiap2026!";

const char* endPoint = "http://api.open-notify.org/iss-now.json";

void setup() {
  Serial.begin(9600);

  // Inicia a conexão do WiFi
  WiFi.begin(ssid, password);

  Serial.print("Conectando..");
  // Poll o status do wifi até ser conectado.
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500); // Embora tenhamos iniciado uma saga contra o delay, nesse caso nada além de esperar conectar o wifi está acontecendo. então tudo bem.
  }

  Serial.println("\nConectado");
}

void loop() {
  int httpResponseCode = 0;

  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String payload; 
    JsonDocument doc;
    float lat, lon;

    // Começa uma requisição http
    http.begin(endPoint);
    // Get
    httpResponseCode = http.GET();

    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);

    // .GET retorna valor negativo em caso de erro
    if(httpResponseCode > 0){
      // pega o "body" da resposta do get
      payload = http.getString();
      Serial.println(payload);

      // Deserealizar o json
      deserializeJson(doc, payload);
      lat = doc["iss_position"]["latitude"];
      lon = doc["iss_position"]["longitude"];

      Serial.print("Latitude: ");
      Serial.println(lat);

      Serial.print("Longitude: ");
      Serial.println(lon);
    }

    // Libera os recursos alocados pelo cliente http
    http.end();
  }
  else
  {
    Serial.println("Wifi desconectado");
  }

  delay(30000); // Espera 30 segundos ants de repetir a requisição
}
