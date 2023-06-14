#include <WiFi.h>
#include <MQTT.h>
#include <DHT.h>

const int DHT_PIN = 2;
DHT dht(DHT_PIN, DHT22);

const char ssid[] = "Wokwi-GUEST";
const char pass[] = "";

WiFiClient net;
MQTTClient client;

float temp = 0;
float hum = 0;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("Dicky Rizqia","dickyrizqia","NO34hVx7vzJL9IGQ")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  //client.subscribe("anton/prafanto/suhu");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("dickyrizqia.cloud.shiftr.io", net);

  connect();
}

void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity(); 

  String suhu = String(temp); //membuat variabel temp untuk di publish ke broker mqtt
  String kelembapan = String(hum); //membuat variabel hum untuk di publish ke broker mqtt

  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    client.publish("dicky/bed/suhu", suhu, true, 1);
    client.publish("dicky/living/suhu", suhu, true, 1);
    client.publish("dicky/kitchen/suhu", suhu, true, 1);
    client.publish("dicky/bath/suhu", suhu, true, 1);
    

    client.publish("dicky/bed/kelembapan", kelembapan, true, 1);
    client.publish("dicky/living/kelembapan", kelembapan, true, 1);
    client.publish("dicky/kitchen/kelembapan", kelembapan, true, 1);
    client.publish("dicky/bath/kelembapan", kelembapan, true, 1);
    
  }
}
