#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "https://projeto-arduino-e1464.firebaseio.com/"
#define FIREBASE_AUTH "jna0HXLdE5eKnQy6frY8rCmIq9CecvRBOkD1Ihtz"
#define WIFI_SSID "NET_2G3B7F5A"
#define WIFI_PASSWORD "5A3B7F5A"

const int LED = 7;

void setupPins(){

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

}

void setupWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado a: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  bool ledVal = Firebase.getBool("ligado");
  digitalWrite(LED, ledVal ? HIGH : LOW);
}

void setup() {
  Serial.begin(9600);

  setupPins();
  setupWifi();    

  setupFirebase();

}

void loop() {

  // Verifica o valor da lampada no firebase 
  bool lampValue = Firebase.getBool("lamp");
  digitalWrite(LED, lampValue ? HIGH : LOW);
  
  delay(200);
}
