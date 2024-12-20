/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);

  pinMode(4, OUTPUT); //led1
  pinMode(15, OUTPUT); //led2
}

// the loop function runs over and over again forever
void loop() {

  


  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(27, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(26, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);

  digitalWrite(14, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(27, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(26, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  digitalWrite(15, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(3000);
  
}
