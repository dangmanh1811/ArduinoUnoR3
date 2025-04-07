#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

// Enter network credentials:
const char* ssid     = "FPTU_Student";
const char* password = "12345678";

// Enter Google Script Deployment ID:
const char *GScriptId = "AKfycbxjKDF0ZwxOYqYZGXA6XpeGiayb5Dy7jzNtaTB5dIdJhw5RsDS5NxUOIzuYBrWLHQE-sw";

// Enter command (insert_row or append_row) and Google Sheets sheet name (default is Sheet1):
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"method\": ";
String payload = "";

// Google Sheets setup (do not edit)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// Declare variables that will be published to Google Sheets
String methodInput = "";
String resultInput = "";

void setup() {

  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");

  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i = 0; i < 5; i++) {
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
      flag = true;
      Serial.println("Connected");
      break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }
  if (!flag) {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    return;
  }
  delete client;    // delete HTTPSRedirect object
  client = nullptr; // delete HTTPSRedirect object
}


void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    
    if (data.startsWith("METHOD=")) {
      methodInput = data.substring(7);
      methodInput.trim();
    } 
    else if (data.startsWith("RESULT=")) {
      resultInput = data.substring(7);
      resultInput.trim();
    }
    
    if (!methodInput.isEmpty() && !resultInput.isEmpty()) {
      sendDataToGoogleSheets(methodInput, resultInput);
      methodInput = "";
      resultInput = "";
    }
  }
  delay(3000);
}

void sendDataToGoogleSheets(String method, String result) {
  static bool flag = false;
  if (!flag) {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr) {
    if (!client->connected()) {
      client->connect(host, httpsPort);
    }
  } else {
    Serial.println("Error creating client object!");
  }

  String payload = payload_base + "\"" + method + "\", \"result\": \"" + result + "\"}";

  Serial.println("Publishing data...");
  Serial.println(payload);
  if (client->POST(url, host, payload)) {
    Serial.println("Data published successfully!");
  } else {
    Serial.println("Error while connecting");
  }
}
