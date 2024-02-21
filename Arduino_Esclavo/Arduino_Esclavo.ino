#define s0 4
#define s1 5
#define s2 6
#define s3 7
#define salidaTCS 8

void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(salidaTCS, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  Serial.begin(9600);
}

void loop() {
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

  if ( rojo >= 203 && rojo <= 212 && verde >= 65 && verde <= 68 && azul >= 65 && azul <= 68){
    Serial.println("VERDE");
  }
    else if ( rojo >= 198 &&  rojo <= 209 && verde >= 55 &&  verde <= 62 && azul >= 60 &&  azul <= 62){
    Serial.println("CELESTE");
  }  
    else if ( rojo >= 150 &&  rojo <= 160 && verde >= 58 &&  verde <= 61 && azul >= 58 &&  azul <= 61){
    Serial.println("AMARILLO");
  }
 }
