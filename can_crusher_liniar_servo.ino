#include <Servo.h>                                                                        // use servo library

int button1         = 5;                                                                  // create a button named button1 on pin 5
int press1          = 0;                                                                  // create button fuction giving it high and low value defult to 0
Servo servo1;                                                                             // create a servo named servo1
bool toggle         = false;                                                              // create varible nammed toggle with true or false (bool = true or false)
bool trigger        = false;                                                              // create varible nammed trigger with true or false (bool = true or false)
bool start          = false;                                                              // create varible nammed start with true or false (bool = true or false)
long startTime      = 0;                                                                  // create varible nammed startTime with long value
long timeToExtend   = 20000;                                                              // create varible nammed timeToExtend with long value  1000 = 1 second
long timeToRetract  = 20000;                                                              // create varible nammed timeToRetract with long value   1000 = 1 second

void setup()
{
  pinMode(button1, INPUT_PULLUP);                                                         // setup pin named button1 defult to pullup (high)
  servo1.attach(9);                                                                       // attach servo to pin 9
  servo1.writeMicroseconds(2000);                                                         // home servo to postion 2000
  Serial.begin(9600);                                                                     // start seiral connection for status monitor 9600 baud rate
}

void loop() {
  press1 = digitalRead(button1);                                                          // monitor button status named button1 of value 0 and 1 (true or false)
  if (press1 == LOW && toggle == false) {                                                 // if button is pressed and toggle is false toggle bool toggle to true
    toggle = true;
  }
  if (press1 == HIGH && toggle == true) {                                                 // if button is not pressed and toggle is true toggle bool to false
    toggle = false;
    trigger = !trigger;                                                                   // change the value of trigger on button press
  }
  Serial.println(trigger);                                                                // print status of button in serial
  moveservo();                                                                            // if the button pressed play this loop names moveservo
}


void moveservo() {
  if (trigger == true && start == false) {                                                // if trigger is true and start is false 
    startTime = millis();                                                                 // start time is clock internal clock value (take photo of clock)
    start = true;                                                                         // then start is true
  }
  if (start == true && millis() < (startTime + timeToExtend) ) {                          // if start is true and internal clock is less than starttime plus timetoextend 
    servo1.writeMicroseconds(1000);                                                       // move servo oll the way out
  }
  if (start == true && millis() > (startTime + timeToExtend) ) {                          // if start is true and internal clock is greater than starttime plus timetoextend
    if (start == true && millis() < (startTime + timeToExtend + timeToRetract) ) {        // if start is true and internal clock is less than starttime plus timetoextend plus timetoretract
      servo1.writeMicroseconds(2000);                                                     // move servo all the way in
    }
  }
  if (start == true && millis() > (startTime + timeToExtend + timeToRetract) ) {          // if start is true and internal clock is greater than starttime plus timetoextend plus timetoretract
    start = false;                                                                        // then start is false
  }
}
