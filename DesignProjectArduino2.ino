//DesignProject2.c
//Austin Teshuba
//This code is for our second arduino with the vibration sensor. 
//It will be used tor trigger a servo motor and launch the coin.

#include <Servo.h>



Servo myservo;//this is the variable to set up the servo


//these are the variables for the button
//int buttonPin = 2;
//int buttonState = 0; // this is a temporary variable to store the status of the button
  //These are the variables for the vibration sensor
  int vibrationPin = 3;//WE WILL NEED ANOTHER ARDUINO
  int servoDelays=0;//this keeps track of how long the servo has been spinning
  long measurement = 0;//This will be used to store the value of the vibration
  bool reset = false;//this is a boolean to reset the apparatus
  bool trigger = false;//this is a flag that will be used to trigger the servo under the right conditions
void setup() {
  // put your setup code here, to run once:
                                                                                                                             
  //this is the setup for the vibration sensor
  pinMode(vibrationPin, INPUT);
  //pinMode(buttonPin, INPUT); //sets up the button pin to read as an input
  Serial.begin(9600);//this allows for the coder to review the inputs

  myservo.attach(9);//attaches the servo on pin 9 to the servo object. 
  myservo.write(91);//makes it stay still
  
  

}

void loop() {
  //button status
  /*
  buttonState = digitalRead(buttonPin);
  if (buttonState==HIGH) {
    myservo.write(2);
    delay(servoDelays);
    servoDelays=0;
    Serial.println("pressed");
  } else {
    Serial.println(buttonState);
  }
*/


  
  // put your main code here, to run repeatedly:
  measurement = TP_init();
  Serial.print("Measurement =");
  Serial.println(measurement);//this will print the vibration number to the console

  //if the vibration is above 1000, this means there has been a significant enough
  // vibration that there is a high liklihood the ball is going through plinko. 
  
  if (measurement>10) {
    myservo.write(0);//starting movement
    //servoDelays+=150;//this adds on the time for the servo turning to the running total. Will be used for resets
    delay(155);//this is purely trial and error, but this allows the servo the generate enough torque
    myservo.write(91);
    delay(200);
    myservo.write(180);
    delay(160);
    myservo.write(91);
    trigger=true;//set trigger to true so this doesnt continue on an infinite loop
    //reset trigger is the reset button is pressed.
  } else {
    myservo.write(91);
  }
}

long TP_init(){
  //This is a function that will collect and return the measurement from the vibration sensor
  delay(10);
  return pulseIn(vibrationPin, HIGH);
}

  
