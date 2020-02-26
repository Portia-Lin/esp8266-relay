#include "index.h"
#include "config.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <EEPROM.h>

byte output = 2;
byte button = 0;
boolean flag = 0;
long lastReconnectAttempt = 0;
String mStatus, mServer, mPort, mUser, mPassword;
const char* mqttServer;
int mqttPort;
const char* mqttUser;
const char* mqttPassword;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
WiFiManager wifiManager;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(output, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(output, LOW);
  Serial.begin(115200);
  Serial.println();
  Serial.println("* * * * *");
  EEPROM.begin(91);
  Serial.println("EEPROM begin");
  WiFi.hostname("ESP8266");
  wifiReset();
  wifiManager.setTimeout(180);
  wifiManager.autoConnect("ESP8266");
  
  server.on("/", indexPage);
  server.on("/config", configPage);
  server.on("/loadConfig", loadConfig);
  server.on("/saveStatus", saveStatus);
  server.on("/saveConfig", saveConfig);
  server.begin();
  
  webSocket.begin();
  Serial.println("[WS] Server started");
  webSocket.onEvent(webSocketEvent);

  eepromRead();

  if (mStatus == "1") {
    Serial.println("MQTT status: true");
    mqttServer = mServer.c_str();
    mqttPort = mPort.toInt();
    mqttUser = mUser.c_str();
    mqttPassword = mPassword.c_str();
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
    }
    client.publish("esp/test", "Hello from ESP8266");
    client.subscribe("esp/test");
  }
  if (mStatus == "0") {
    Serial.println("MQTT status: false"); 
  }
}

void loop() {
  checkButton();
  server.handleClient();
  webSocket.loop();
  if (mStatus == "1" && !client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      Serial.println("MQTT status: Connection error");
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
        Serial.println("mqtt connected");
      }
    }
  } else {
    // Client connected

    client.loop();
  }
}

void indexPage() {
  String view = INDEX_PAGE;
  server.send(200, "text/html", view);
}

void configPage() {
  String view = CONFIG_PAGE;
  server.send(200, "text/html", view);
}

void loadConfig() {
  String json = "{";
  json += "\"mqtt_status\":\"";
  json += mStatus;
  json += "\",\"mqtt_server\":\"";
  json += mServer;
  json += "\",\"mqtt_port\":\"";
  json += mPort;
  json += "\",\"mqtt_user\":\"";
  json += mUser;
  json += "\",\"mqtt_password\":\"";
  json += mPassword;
  json += "\"}";
  server.send(200, "text/json", json);
}

void saveStatus() {
  server.send(200, "text/html");
  
  // Status
  EEPROM.write(0, server.arg("mqtt_status")[0]);
  EEPROM.commit();
  Serial.println("Status successfully saved");
}

void saveConfig() {
  server.send(200, "text/html");
  for (int i = 1; i <=90 ; ++i) { EEPROM.write(i, 0); }

  // Server
  for (int i = 0; i < server.arg("mqtt_server").length(); i++) {
    EEPROM.write(1+i, server.arg("mqtt_server")[i]);
  }

  //Port
  for (int i = 0; i < server.arg("mqtt_port").length(); i++) {
    EEPROM.write(31+i, server.arg("mqtt_port")[i]);
  }

  // User
  for (int i = 0; i < server.arg("mqtt_user").length(); i++) {
    EEPROM.write(36+i, server.arg("mqtt_user")[i]);
  }

  // Password
  for (int i = 0; i < server.arg("mqtt_password").length(); i++) {
    EEPROM.write(61+i, server.arg("mqtt_password")[i]);
  }

  EEPROM.commit();
  Serial.println("Сonfiguration successfully saved");
}

void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.print("[WS] Type ");
      Serial.print(type);
      Serial.println(": DISCONNECTED");
      break;
    case WStype_CONNECTED:
      broadcastState();
      Serial.print("[WS] Type ");
      Serial.print(type);
      Serial.println(": CONNECTED");
      break;
    case WStype_TEXT:
      if (payload[0] == 't') {
        digitalWrite(output, !digitalRead(output));
        broadcastState();
      }
      break;
  }
}

void broadcastState() {
  if (digitalRead(output) == HIGH) {
    webSocket.broadcastTXT("0");
    Serial.println("State: HIGH");
  }
  if (digitalRead(output) == LOW) {
    Serial.println("State: LOW");
    webSocket.broadcastTXT("1");
  }
}

void checkButton() {
  if (digitalRead(button) == LOW && flag == 0) {
    flag = 1;
    digitalWrite(output, !digitalRead(output));
    broadcastState();
  }
  if (digitalRead(button) == HIGH && flag == 1) {
    flag = 0;
  }
}

void eepromRead() {
  // Status
  mStatus += char(EEPROM.read(0));
  
  // Server
  for (int i = 1; i <= 30; i++) {
    if (char(EEPROM.read(i)) != 0x00) {
      mServer += char(EEPROM.read(i));
    }
  }

  // Port
  for (int i = 31; i <= 35; i++) {
    if (char(EEPROM.read(i)) != 0x00) {
      mPort += char(EEPROM.read(i));
    }
  }

  // User
  for (int i = 36; i <= 60; i++) {
    if (char(EEPROM.read(i)) != 0x00) {
      mUser += char(EEPROM.read(i));
    }
  }

  // Password
  for (int i = 61; i <= 90; i++){
    if (char(EEPROM.read(i)) != 0x00) {
      mPassword += char(EEPROM.read(i));
    }
  }
  Serial.println("EEPROM read");
}

void wifiReset() {
  Serial.println("Waiting for reset wifi!");
  for (int i = 0; i < 4; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  if(digitalRead(0) == LOW) {
    wifiManager.resetSettings();
    Serial.println("Reset saved settings!");
  }
}

boolean reconnect() {
  if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
    // Once connected, publish an announcement...
    client.publish("esp/test", "Hello from ESP8266");
    // ... and resubscribe
    client.subscribe("esp/test");
  }
  return client.connected();
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
}
