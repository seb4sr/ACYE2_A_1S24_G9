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

    if (rojo >= 420 && rojo <= 530 && verde >= 200 && verde <= 350 && azul >= 200 && azul <= 250) {
      Serial.println("ROJO");
      CODE = 1;
    } else if (rojo >= 700 && rojo <= 810 && verde >= 155 && verde <= 200 && azul >= 155 && azul <= 195) {
      Serial.println("CELESTE");
      CODE = 2;
    } else if (rojo >= 340 && rojo <= 400 && verde >= 115 && verde <= 160 && azul >= 115 && azul <= 150) {
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

    if(pingTravelTime >= 150 && pingTravelTime <= 295){
      Serial.println("GRANDE");
    }else if (pingTravelTime >= 300 && pingTravelTime<= 350){
      Serial.println("MEDIANO");
    }else if (pingTravelTime>=420 && pingTravelTime<= 500){
      Serial.println("PEQUENO");
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
