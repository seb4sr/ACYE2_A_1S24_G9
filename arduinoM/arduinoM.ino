#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define motorpin1 A3
#define motorpin2 A2
#define motorpin3 A1
#define motorpin4 A0

#define motorsteps 200
Stepper motorder(motorsteps, motorpin1, motorpin3, motorpin2, motorpin4);

int trigPin = 7;
int echoPin = 6;
int pingTravelTime;


int pasosVuelta = 2048;
bool vuelt = true;
int i = 0;
int btnEmergencia = 12;
int CR = 0;
int CAZ = 0;
int CA = 0;
int G = 0;
int M = 0;
int P = 0;

Stepper motor(pasosVuelta, 8, 10, 9, 11);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines de los botones
const int btnUpPin = 2;
const int btnDownPin = 3;
const int btnSelectPin = 4;
const int btnBackPin = 5;

int estado = 1;
byte CODE;
byte filtro = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  motor.setSpeed(15);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btnEmergencia, INPUT_PULLUP);

  CR = EEPROM.read(0);
  CAZ = EEPROM.read(1);
  CA = EEPROM.read(2);

  G = EEPROM.read(3);
  M = EEPROM.read(4);
  P = EEPROM.read(5);

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
  Wire.beginTransmission(0x01);
  Wire.write(filtro);
  Wire.endTransmission();

  motorder.setSpeed(15);
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);
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
    if (filtro == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Contador: ");
      lcd.setCursor(0, 1);
      lcd.print("VERDE: ");
      lcd.print(CR);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Contador: ");
      lcd.setCursor(0, 1);
      lcd.print("GRANDE: ");
      lcd.print(G);
    }
    estado = 5;
    delay(300);
  } else if (estado == 5 && digitalRead(btnDownPin) == LOW) {
    lcd.clear();
    if (filtro == 0) {
      lcd.setCursor(0, 0);
      lcd.print("CELESTE: ");
      lcd.print(CAZ);
      lcd.setCursor(0, 1);
      lcd.print("AMARILLO: ");
      lcd.print(CA);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("MEDIANO: ");
      lcd.print(M);
      lcd.setCursor(0, 1);
      lcd.print("PEQUENO: ");
      lcd.print(P);
    }
    estado = 12;
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
    EEPROM.write(0, 0);
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);
    EEPROM.write(3, 0);
    EEPROM.write(4, 0);
    EEPROM.write(5, 0);
    CR = 0;
    CAZ = 0;
    CA = 0;
    G = 0;
    M = 0;
    P = 0;
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
  } else if (estado == 12 && digitalRead(btnBackPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Histrorial");
    lcd.setCursor(1, 1);
    lcd.print("Filtro");
    estado = 1;
    delay(300);
  } else if (estado == 12 && digitalRead(btnUpPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contador: ");
    lcd.setCursor(0, 1);
    lcd.print("ROJO: ");
    lcd.print(CR);
    estado = 5;
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
    filtro = 0;
    Wire.beginTransmission(0x01);
    Wire.write(filtro);
    Wire.endTransmission();
    delay(300);
  } else if (estado == 7 && digitalRead(btnSelectPin) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Filtro: Size");
    filtro = 1;
    Wire.beginTransmission(0x01);
    Wire.write(filtro);
    Wire.endTransmission();
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
    while (i < 10) {
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
        if (i == 0 && filtro == 0) {
          delay(5000);
          Wire.requestFrom(0x01, 1);
          while (Wire.available()) {
            CODE = Wire.read();
          }
          if (CODE == 1) {
            CR = CR + 1;
            EEPROM.write(0, CR);
          } else if (CODE == 2) {
            CAZ = CAZ + 1;
            EEPROM.write(1, CAZ);
            motorder1();
          } else if (CODE == 3) {
            CA = CA + 1;
            EEPROM.write(2, CA);
          }
        } else if (i == 1 && filtro == 1) {
          delay(5000);
          Wire.requestFrom(0x01, 1);
          while (Wire.available()) {
            CODE = Wire.read();
          }
          if (CODE == 4) {
            G = G + 1;
            EEPROM.write(3, G);
          } else if (CODE == 5) {
            M = M + 1;
            EEPROM.write(4, M);
          } else if (CODE == 6) {
            P = P + 1;
            EEPROM.write(5, P);
          }
        }
      }
      i += 1;
    }
    Serial.println(CODE);
    if (CODE == 1) {
      CR = CR + 1;
      EEPROM.write(0, CR);
    } else if (CODE == 2) {
      CAZ = CAZ + 1;
      EEPROM.write(1, CAZ);
      motorder2();
    } else if (CODE == 3) {
      CA = CA + 1;
      EEPROM.write(2, CA);
    }

    delay(500);
    //Serial.println("se logra");
    i = 0;
    delay(100);
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

void motorder1() {
  motorder.step(-260);
  delay(1000);
}
void motorder2() {
  motorder.step(260);
  delay(1000);
}