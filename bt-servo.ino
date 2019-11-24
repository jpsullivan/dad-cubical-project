#include <Servo.h>

Servo myServo1; // instantiate servo object to control servo 1
Servo myServo2;
Servo myServo3;
Servo myServo4;

int ledPin = 13;
int state = 0;
int flag = 0;

int servoPos = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  myServo1.attach(3); // attach servo1 signal wire to pin3 (pwm)
  myServo2.attach(5); // attach servo2 signal wire to pin5 (pwm)
  myServo3.attach(6); // attach servo3 signal wire to pin6 (pwm)
  myServo4.attach(9); // attach servo4 signal wire to pin9 (pwm)
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    state = Serial.read();
    flag = 0;
  }
  if (state == '0')
  {
    // turn the led off
    digitalWrite(ledPin, LOW);

    // reset the position of servo1
    servoPos = 0;
    myServo1.write(servoPos);
    myServo2.write(servoPos);
    myServo3.write(servoPos);
    myServo4.write(servoPos);

    if (flag == 0)
    {
      Serial.println("LED: Off");
      flag = 1;
    }
  }
  else if (state == '1')
  {
    // turn the led on
    digitalWrite(ledPin, HIGH);

    for (servoPos = 0; servoPos <= 90; servoPos += 1)
    {
      // interate in steps of 1 degree
      myServo1.write(servoPos);
      myServo2.write(servoPos);
      myServo3.write(servoPos);
      myServo4.write(servoPos);
      Serial.println(myServo1.read());
      delay(15); // wait 15ms until next iteration
    }

    // decrement the servo position to complete the "sweep"
    for (servoPos = 90; servoPos >= 0; servoPos -= 1)
    {
      myServo1.write(servoPos);
      myServo2.write(servoPos);
      myServo3.write(servoPos);
      myServo4.write(servoPos);
      delay(15);
    }

    if (flag == 0)
    {
      Serial.println("LED: On");
      flag = 1;
    }
  }
}