/*
 * Motor Controller Board for Rover Robot
 */

int leftFwd = 3;
int leftRev = 5;
int rightFwd = 6;
int rightRev = 9;

void setup() {
  pinMode(leftFwd, OUTPUT);
  pinMode(leftRev, OUTPUT);
  pinMode(rightFwd, OUTPUT);
  pinMode(rightRev, OUTPUT);

  Serial.begin(9600);  
  while(! Serial);
  Serial.println("READY");
}

void loop() {
  static int nextSpeed=0;
  static int leftSpeed=0;
  static int rightSpeed=0;
  
  if(Serial.available()) {
      int speed = Serial.parseInt();
      if(nextSpeed) {
        rightSpeed = speed;
        nextSpeed = 0;
      }  else {
        leftSpeed = speed;
        nextSpeed = 1;
      }
  }

  //send the speeds to the motors, changing directions as needed.
  if(leftSpeed >= 0) {
    analogWrite(leftFwd, leftSpeed);
    analogWrite(leftRev, 0);
  } else {
    analogWrite(leftFwd, 0);
    analogWrite(leftRev, -leftSpeed);
  }

  if(rightSpeed >=0) {
    analogWrite(rightFwd, rightSpeed);
    analogWrite(rightRev, 0);
  } else {
    analogWrite(rightFwd, 0);
    analogWrite(rightRev, rightSpeed);
  }
}
