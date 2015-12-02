
int LED=13;
int sensorEnable=5;
int sensorRead=9;

int reflectionSense(int pin) {
  if(digitalRead(pin) == HIGH) {
    return false;  
  } else {
    return true;
  }
}


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(sensorEnable, OUTPUT);
  pinMode(sensorRead, INPUT);
  digitalWrite(sensorEnable, HIGH);
}

void loop() {
  if(reflectionSense(sensorRead)) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
