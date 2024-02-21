#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int trigPin = 7;
int echoPin = 6;
int pingTravelTime;


int pasosVuelta = 2048;
bool vuelt = true;
int i = 0;
int btnEmergencia = 12;

Stepper motor(pasosVuelta, 8, 10, 9, 11);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines de los botones
const int btnUpPin = 5;
const int btnDownPin = 4;
const int btnSelectPin = 3;
const int btnBackPin = 2;

int estado = 1;

void setup() {
  Serial.begin(9600);
  motor.setSpeed(15);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btnEmergencia, INPUT_PULLUP);

  pinMode(btnUpPin, INPUT_PULLUP);
  pinMode(btnDownPin, INPUT_PULLUP);
  pinMode(btnSelectPin, INPUT_PULLUP);
  pinMode(btnBackPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("<Grupo9_A_1S24>");
  lcd.setCursor(3, 1);
  lcd.print("Practica 2");
  delay(1000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(">Histrorial");
  lcd.setCursor(1, 1);
  lcd.print("Filtro");
}

void loop() {
  if (estado == 1 && digitalRead(btnDownPin) == LOW) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Histrorial");
    lcd.setCursor(0, 1);
    lcd.print(">Filtro");
    estado = 2;
    delay(300);
  } else if (estado == 2 && digitalRead(btnDownPin) == LOW) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Filtro");
    lcd.setCursor(0, 1);
    lcd.print(">Reset");
    estado = 3;
    delay(300);
  } else if (estado == 3 && digitalRead(btnUpPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Filtro");
    lcd.setCursor(1, 1);
    lcd.print("Reset");
    estado = 2;
    delay(300);
  } else if (estado == 2 && digitalRead(btnUpPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Histrorial");
    lcd.setCursor(1, 1);
    lcd.print("Filtro");
    estado = 1;
    delay(300);
  } else if (estado == 1 && digitalRead(btnSelectPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contador: ");
    lcd.setCursor(0, 1);
    lcd.print("NUMERO");
    estado = 5;
    delay(300);
  } else if (estado == 2 && digitalRead(btnSelectPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Color");
    lcd.setCursor(1, 1);
    lcd.print("Size");
    estado = 6;
    delay(300);
  } else if (estado == 6 && digitalRead(btnDownPin) == LOW) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Color");
    lcd.setCursor(0, 1);
    lcd.print(">Size");
    estado = 7;
    delay(300);
  } else if (estado == 7 && digitalRead(btnUpPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Color");
    lcd.setCursor(0, 1);
    lcd.print("Size");
    estado = 6;
    delay(300);
  } else if (estado == 3 && digitalRead(btnSelectPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Se Reseteo");
    estado = 9;
    delay(300);
  } else if (estado == 5 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Histrorial");
    lcd.setCursor(1, 1);
    lcd.print("Filtro");
    estado = 1;
    delay(300);
  } else if (estado == 6 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Filtro");
    lcd.setCursor(1, 1);
    lcd.print("Reset");
    estado = 2;
    delay(300);
  } else if (estado == 7 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Filtro");
    lcd.setCursor(1, 1);
    lcd.print("Reset");
    estado = 2;
    delay(300);
  } else if (estado == 9 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Filtro");
    lcd.setCursor(0, 1);
    lcd.print(">Reset");
    estado = 3;
    delay(300);
  } else if (estado == 6 && digitalRead(btnSelectPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Filtro: Color");
    estado = 10;
    delay(300);
  } else if (estado == 7 && digitalRead(btnSelectPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Filtro: Size");
    estado = 11;
    delay(300);
  } else if (estado == 10 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Color");
    lcd.setCursor(1, 1);
    lcd.print("Size");
    estado = 6;
    delay(300);
  } else if (estado == 11 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Color");
    lcd.setCursor(0, 1);
    lcd.print(">Size");
    estado = 7;
    delay(300);
  }

  if (Sensor()) {
    while (i < 8) {
      if (digitalRead(btnEmergencia) == LOW) {
        Serial.println("Emergencia");

        for (int i = 5; i > 0; i--) {
          Serial.print(i);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Emergencia");
          lcd.setCursor(5, 1);
          lcd.print("Espere ");
          lcd.print(i);
          lcd.print("s");
          delay(1000);
        }
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print(">Histrorial");
        lcd.setCursor(1, 1);
        lcd.print("Filtro");
        estado = 1;

        break;
      } else {
        motor.step(-pasosVuelta);
        i += 1;
      }
    }
    delay(5000);
    Serial.println("se logra");
    i = 0;
  }
}

int Sensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pingTravelTime = pulseIn(echoPin, HIGH);
  Serial.println(pingTravelTime);

  if (pingTravelTime < 520 && pingTravelTime != 0) {
    Serial.println("Objeto detectado");
    return true;
  } else {
    Serial.println("Ningún objeto detectado");
    return false;
  }
}