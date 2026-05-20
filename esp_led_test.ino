#define LED_BUILTIN 2   // ESP32 built-in LED pin

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // ON
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);  // OFF
  delay(1000);
}