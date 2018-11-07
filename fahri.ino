

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(25);
  myservo2.attach(26);
  myservo3.attach(27);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(360);
  delay(1000);
  myservo2.write(0);
  delay(1000);
  myservo3.write(400);// tell servo to go to position in variable 'pos'
  delay(2000);

  
  myservo.write(0);
  delay(1000);
  myservo2.write(360);
  delay(1000);
  myservo3.write(0);
  0delay(1000);
   
  
 
}
