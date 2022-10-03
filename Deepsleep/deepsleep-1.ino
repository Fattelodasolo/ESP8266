int tempo = 5e6;        // 5 secondi in notazione esponenziale 5x10^6

void setup() {
  Serial.begin(9600);
  
  Serial.println("Sveglio!");

  pinMode(LED_BUILTIN,OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  ESP.deepSleep(tempo);
}

void loop() {
}
