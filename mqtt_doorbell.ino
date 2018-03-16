#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>

#define wifi_ssid "SSID"
#define wifi_password "PASSWORD"

#define mqtt_server "IP_ADDRESS"
#define topic "smarthome"

#define INTPIN  D4

Ticker flipper;
WiFiClient espClient;
PubSubClient client(espClient);

int pin = 0;

void setup() {
  Serial.begin(115200);
  //pinMode(INTPIN, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  attachInterrupt(digitalPinToInterrupt(INTPIN), IntCallback, FALLING);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    if (client.connect("smarthome")) {
      //if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void IntCallback() {
  client.publish(topic,"doorbell,zone=gate value=0", false);
  detachInterrupt(digitalPinToInterrupt(INTPIN));
  flipper.attach(20, flip); // debug on
}

void flip() {
  client.publish(topic,"doorbell,zone=gate value=0", false);
  attachInterrupt(digitalPinToInterrupt(INTPIN), IntCallback, FALLING);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

