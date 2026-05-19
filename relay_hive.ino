#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <DNSServer.h>
#include <PubSubClient.h>

#define WIFI_LED 2

// -------- RELAY PINS --------
#define RELAY1 18
#define RELAY2 19
#define RELAY3 21
#define RELAY4 22

WebServer server(80);
Preferences preferences;
DNSServer dnsServer;

const byte DNS_PORT = 53;

// -------- MQTT --------
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// -------- WIFI --------
String ssid = "";
String password = "";

bool wifiConnected = false;

// ---------------- HTML PAGE ----------------
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
  <title>ESP32 Relay Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body style="font-family:Arial; text-align:center; margin-top:40px;">

<h2>ESP32 WiFi Setup</h2>

<form action="/save">

<input type="text" name="ssid" placeholder="WiFi Name"
style="width:250px;height:35px;font-size:18px;"><br><br>

<input type="password" name="pass" placeholder="Password"
style="width:250px;height:35px;font-size:18px;"><br><br>

<input type="submit" value="Connect WiFi"
style="width:180px;height:40px;font-size:18px;">

</form>

<hr>

<h2>4 RELAY CONTROL</h2>

<a href="/r1on"><button style="width:120px;height:50px;">Relay1 ON</button></a>
<a href="/r1off"><button style="width:120px;height:50px;">Relay1 OFF</button></a>

<br><br>

<a href="/r2on"><button style="width:120px;height:50px;">Relay2 ON</button></a>
<a href="/r2off"><button style="width:120px;height:50px;">Relay2 OFF</button></a>

<br><br>

<a href="/r3on"><button style="width:120px;height:50px;">Relay3 ON</button></a>
<a href="/r3off"><button style="width:120px;height:50px;">Relay3 OFF</button></a>

<br><br>

<a href="/r4on"><button style="width:120px;height:50px;">Relay4 ON</button></a>
<a href="/r4off"><button style="width:120px;height:50px;">Relay4 OFF</button></a>

</body>
</html>
)rawliteral";

// ---------------- ROOT ----------------
void handleRoot() {

  server.send(200, "text/html", htmlPage);
}

// ---------------- SAVE WIFI ----------------
void handleSave() {

  ssid = server.arg("ssid");
  password = server.arg("pass");

  Serial.println("\n========== WIFI RECEIVED ==========");

  Serial.print("SSID : ");
  Serial.println(ssid);

  Serial.print("PASS : ");
  Serial.println(password);

  preferences.begin("wifi", false);

  preferences.putString("ssid", ssid);
  preferences.putString("pass", password);

  preferences.end();

  server.send(200, "text/html",
              "<h2>WiFi Saved</h2>"
              "<h3>ESP32 Restarting...</h3>");

  delay(3000);

  ESP.restart();
}

// ---------------- RELAY WEBSITE CONTROL ----------------

void relay1ON() {
  digitalWrite(RELAY1, LOW);
  Serial.println("Relay1 ON");
  server.send(200, "text/html", htmlPage);
}

void relay1OFF() {
  digitalWrite(RELAY1, HIGH);
  Serial.println("Relay1 OFF");
  server.send(200, "text/html", htmlPage);
}

void relay2ON() {
  digitalWrite(RELAY2, LOW);
  Serial.println("Relay2 ON");
  server.send(200, "text/html", htmlPage);
}

void relay2OFF() {
  digitalWrite(RELAY2, HIGH);
  Serial.println("Relay2 OFF");
  server.send(200, "text/html", htmlPage);
}

void relay3ON() {
  digitalWrite(RELAY3, LOW);
  Serial.println("Relay3 ON");
  server.send(200, "text/html", htmlPage);
}

void relay3OFF() {
  digitalWrite(RELAY3, HIGH);
  Serial.println("Relay3 OFF");
  server.send(200, "text/html", htmlPage);
}

void relay4ON() {
  digitalWrite(RELAY4, LOW);
  Serial.println("Relay4 ON");
  server.send(200, "text/html", htmlPage);
}

void relay4OFF() {
  digitalWrite(RELAY4, HIGH);
  Serial.println("Relay4 OFF");
  server.send(200, "text/html", htmlPage);
}

// ---------------- MQTT CALLBACK ----------------
void callback(char* topic, byte* payload, unsigned int length) {

  String message;

  for (int i = 0; i < length; i++) {

    message += (char)payload[i];
  }

  Serial.print("MQTT Message : ");
  Serial.println(message);

  // Relay 1
  if (message == "R1ON") digitalWrite(RELAY1, LOW);
  if (message == "R1OFF") digitalWrite(RELAY1, HIGH);

  // Relay 2
  if (message == "R2ON") digitalWrite(RELAY2, LOW);
  if (message == "R2OFF") digitalWrite(RELAY2, HIGH);

  // Relay 3
  if (message == "R3ON") digitalWrite(RELAY3, LOW);
  if (message == "R3OFF") digitalWrite(RELAY3, HIGH);

  // Relay 4
  if (message == "R4ON") digitalWrite(RELAY4, LOW);
  if (message == "R4OFF") digitalWrite(RELAY4, HIGH);
}

// ---------------- MQTT RECONNECT ----------------
void reconnectMQTT() {

  while (!client.connected()) {

    Serial.println("Connecting MQTT...");

    String clientID = "ESP32-" + String(random(1000, 9999));

    if (client.connect(clientID.c_str())) {

      Serial.println("MQTT Connected Successfully");

      client.subscribe("home/relay");

      Serial.println("Subscribed To : home/relay");
    }

    else {

      Serial.print("MQTT Failed : ");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

// ---------------- START HOTSPOT ----------------
void startHotspot() {

  Serial.println("\nSTARTING HOTSPOT");

  wifiConnected = false;

  digitalWrite(WIFI_LED, LOW);

  WiFi.disconnect(true);

  delay(1000);

  WiFi.mode(WIFI_AP);

  WiFi.softAP("ESP32_Setup", "12345678");

  delay(1000);

  IPAddress IP = WiFi.softAPIP();

  Serial.print("Portal IP : ");
  Serial.println(IP);

  dnsServer.start(DNS_PORT, "*", IP);

  // Routes
  server.on("/", handleRoot);

  server.on("/save", handleSave);

  server.on("/r1on", relay1ON);
  server.on("/r1off", relay1OFF);

  server.on("/r2on", relay2ON);
  server.on("/r2off", relay2OFF);

  server.on("/r3on", relay3ON);
  server.on("/r3off", relay3OFF);

  server.on("/r4on", relay4ON);
  server.on("/r4off", relay4OFF);

  // Captive Portal Redirect
  server.onNotFound([]() {

    server.sendHeader(
      "Location",
      String("http://") + WiFi.softAPIP().toString(),
      true);

    server.send(302, "text/plain", "");
  });

  server.begin();

  Serial.println("Web Server Started");
}

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);

  randomSeed(micros());

  pinMode(WIFI_LED, OUTPUT);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // Relay OFF initially (ACTIVE LOW)
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  digitalWrite(WIFI_LED, LOW);

  Serial.println("\nESP32 STARTING");

  // -------- READ SAVED WIFI --------
  preferences.begin("wifi", true);

  ssid = preferences.getString("ssid", "");
  password = preferences.getString("pass", "");

  preferences.end();

  // -------- CONNECT TO WIFI --------
  if (ssid != "") {

    Serial.print("Connecting To : ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid.c_str(), password.c_str());

    int timeout = 0;

    while (WiFi.status() != WL_CONNECTED && timeout < 20) {

      delay(500);

      Serial.print(".");

      timeout++;
    }

    // -------- WIFI SUCCESS --------
    if (WiFi.status() == WL_CONNECTED) {

      Serial.println("\nWiFi Connected");

      Serial.print("ESP32 IP : ");
      Serial.println(WiFi.localIP());

      wifiConnected = true;

      digitalWrite(WIFI_LED, HIGH);

      // Website routes
      server.on("/", handleRoot);

      server.on("/r1on", relay1ON);
      server.on("/r1off", relay1OFF);

      server.on("/r2on", relay2ON);
      server.on("/r2off", relay2OFF);

      server.on("/r3on", relay3ON);
      server.on("/r3off", relay3OFF);

      server.on("/r4on", relay4ON);
      server.on("/r4off", relay4OFF);

      server.begin();

      Serial.println("Web Server Started");

      // MQTT Setup
      client.setServer(mqtt_server, 1883);

      client.setCallback(callback);

      return;
    }

    // -------- WIFI FAILED --------
    else {

      Serial.println("\nWiFi Failed");

      startHotspot();
    }
  }

  // -------- NO WIFI SAVED --------
  else {

    Serial.println("No WiFi Saved");

    startHotspot();
  }
}

// ---------------- LOOP ----------------
void loop() {

  // WiFi Lost
  if (wifiConnected && WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi Lost!");

    digitalWrite(WIFI_LED, LOW);

    startHotspot();
  }

  // Hotspot DNS
  if (!wifiConnected) {

    dnsServer.processNextRequest();
  }

  // Web Server
  server.handleClient();

  // MQTT
  if (wifiConnected) {

    if (!client.connected()) {

      reconnectMQTT();
    }

    client.loop();
  }
}