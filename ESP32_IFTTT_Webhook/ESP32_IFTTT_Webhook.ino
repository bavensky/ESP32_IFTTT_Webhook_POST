#include <WiFi.h>;
#include <HTTPClient.h>;

const char* ssid = "your ssid name";
const char* password =  "your wifi password";

const char* ifttt_event =  "your event name";
const char* ifttt_key =  "your ifttt key";

uint32_t pevTime = 0;
int value1, value2, value3;

void iftttPost(int value1, int value2, int value3) {
  HTTPClient http;

  http.begin("https://maker.ifttt.com/trigger/" + String(ifttt_event) + "/with/key/" + String(ifttt_key));
  http.addHeader("Content-Type", "application/json");

  // HTTP POST Format = {"value1":"hello","value2":"super","value3":"man"}
  String postData = "{\"value1\":\"" + String(value1) + "\",\"value2\":\"" + String(value2) + "\",\"value3\":\"" + String(value3) + "\"}";
  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (millis() - pevTime > 5 * 1000) {
      pevTime = millis();

      // random value
      value1 = random(1, 10);
      value2 = random(11, 20);
      value3 = random(21, 30);

      iftttPost(value1, value2, value3);  // HTTP POST to trig ifttt event
    }
  } else {
    Serial.println("Error in WiFi connection");
    WiFi.begin(ssid, password);
  }
}
