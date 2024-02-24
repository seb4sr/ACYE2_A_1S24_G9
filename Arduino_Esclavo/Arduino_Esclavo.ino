#include "Wire.h"
#define s0 4
#define s1 5
#define s2 6
#define s3 7
#define salidaTCS 8

bool cont = true;
byte CODE;
byte entra = 0;

int trigPin = 12;
int echoPin = 11;
int pingTravelTime;




void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(salidaTCS, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  Serial.begin(9600);

  Wire.begin(0x01);
  Wire.onReceive(EntradaSolicitud);
  Wire.onRequest(Peticion);
}

void loop() {
  if (entra == 0) {
    digitalWrite(s2, LOW);
    digitalWrite(s2, LOW);
    int rojo = pulseIn(salidaTCS, LOW);
    delay(200);

    digitalWrite(s2, HIGH);
    digitalWrite(s2, HIGH);
    int verde = pulseIn(salidaTCS, LOW);
    delay(200);

    digitalWrite(s2, LOW);
    digitalWrite(s2, HIGH);
    int azul = pulseIn(salidaTCS, LOW);
    delay(200);

    Serial.print("R: ");
    Serial.print(rojo);

    Serial.print("\t");

    Serial.print("V: ");
    Serial.print(verde);

    Serial.print("\t");

    Serial.print("A: ");
    Serial.print(azul);

    Serial.print("\n");

    if (rojo >= 100 && rojo <= 130 && verde >= 35 && verde <= 45 && azul >= 50 && azul <= 60) {
      Serial.println("VERDE");
      CODE = 1;
    } else if (rojo >= 180 && rojo <= 245 && verde >= 45 && verde <= 80 && azul >= 65 && azul <= 75) {
      Serial.println("CELESTE");
      CODE = 2;
    } else if (rojo >= 75 && rojo <= 90 && verde >= 35 && verde <= 40 && azul >= 40 && azul <= 50) {
      Serial.println("AMARILLO");
      CODE = 3;
    }
  } else {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    pingTravelTime = pulseIn(echoPin, HIGH);
    digitalWrite(trigPin, LOW);
    Serial.println(pingTravelTime);

    if(pingTravelTime >= 150 && pingTravelTime <= 210){
      Serial.println("GRANDE");
      CODE = 4;
    }else if (pingTravelTime >= 240 && pingTravelTime<= 290){
      Serial.println("MEDIANO");
      CODE = 5;
    }else if (pingTravelTime>=420 && pingTravelTime<= 500){
      Serial.println("PEQUENO");
      CODE = 6;
    }
  }
}

//-------EVENTO DE ENTRADA--- ENVIADO POR EL MAESTRO---
void EntradaSolicitud(int re) {
  while (Wire.available()) {
    entra = Wire.read();
  }
  Serial.print("entra ");
  Serial.println(entra);
}
//-----EVENTO DE PETICIÓN--- SOLICITADO POR EL MAESTRO---
void Peticion() {
  Serial.println(CODE);
  Wire.write(CODE);
}