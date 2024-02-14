#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#if!defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!Please run `make menuconfig`
to and enable it
#endif

// Define WiFi credentials
#define ssid "enter_wi_fi_ssid"
#define password "enter_wi_fi_password"

WiFiClient client;
HTTPClient http;
String API1 = "http://proiectia.bogdanflorea.ro/api/south-park-episodes/episodes";
String API2 = "http://proiectia.bogdanflorea.ro/api/south-park-episodes/episode/";

bool deviceConnected = false;

// BTC server name
#define btcServerName "B&S Electronics"

#define SERVICE_UUID "801a9d03-6a1a-4985-a634-64386dc86346"

// Define the BluetoothSerial
BluetoothSerial SerialBT;

// Received data
String data = "";

// The receivedData function is called when data is available on Bluetooth (see loop function)
void receivedData() {
  // Read the data using the appropriate SerialBT functions
  // according to the app specifications
  // The data is terminated by the new line character (\n)
  while (SerialBT.available()) {
    data = SerialBT.readStringUntil('\n');
  }

  Serial.println(data); // <-- This is the message sent from the app, according to the specs
  DynamicJsonDocument jsonCommand(216);
  DeserializationError error = deserializeJson(jsonCommand, data);
  if (error)
    Serial.println(error.c_str());
  else {
    String current_API;
    if (jsonCommand["action"] == "fetchData") {
      current_API = API1;
    } else
      current_API = API2 + jsonCommand["id"].as < String > ();
    if (WiFi.status() == WL_CONNECTED) {
      http.setTimeout(10000);
      http.end();
      http.begin(current_API);
      if (http.GET() == 200) {
        DynamicJsonDocument jsonInput(15000);
        Serial.println("Incepe deserializarea");
        String httpInput = http.getString();
        if (jsonCommand["action"] == "fetchDetails")
          httpInput = "[" + httpInput + " ]";
        Serial.print(httpInput);
        DeserializationError error = deserializeJson(jsonInput, httpInput);
        if (error) {
          Serial.println(error.c_str());
          Serial.print("Eroare la deserializare");
        } else {
          Serial.println("Incepe sa formeze jsonOutput");
          JsonArray LIST = jsonInput.as < JsonArray > ();
          for (JsonVariant listItem: LIST) {
            DynamicJsonDocument jsonOutput(1000);
            JsonObject objOutput = jsonOutput.to < JsonObject > ();
            if (objOutput.isNull())
              Serial.println("Crearea lui objOutput a esuat");
            else {
              String output;
              objOutput["id"] = listItem["id"].as < String > ();
              objOutput["name"] = listItem["name"].as < String > ();
              objOutput["image"] = listItem["thumbnail_url"].as < String > ();
              objOutput["description"] = "Season: " + listItem["season"].as < String > () + " Episode: " + listItem["episode"].as < String > () + " Air date: " + listItem["air_date"].as < String > () + " " + listItem["description"].as < String > ();
              serializeJson(jsonOutput, output);
              // Add a small delay (100-200ms)     
              SerialBT.println(output);
              Serial.println(output);
              delay(100);
            }
          }
        }
      } else {
        Serial.println("A avut loc o eroare la cererea de tip GET.");
      }
    }
  }
  // Reset the received data string after processing 
  data = "";
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // TODO -- Connect WiFi
  // TODO -- Write your code
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WIFI is CONECTED");
  // No need to change the lines below
  // Initialize BTC
  SerialBT.begin(btcServerName); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // Check available Bluetooth data and perform read from the app
  if (SerialBT.available()) {
    receivedData();
  }
}
