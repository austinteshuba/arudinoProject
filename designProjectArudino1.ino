#include <Servo.h>

/* DesignProject.c
 *  By Austin Teshuba
 *  This code is to operate a servo motor as well as a TSC3200 RGB color sensor. 
*/

// I previously used a motion sensor to determine if the domino was there. This was innaccurate and failed to trigger. I changed this to a color sensor. 

#include <Servo.h>


int S0 = 7; // this is the pin for S0 on the color sensor
int S1 = 3; // this is the pin for S1 on the color sensor
int S2 = 10;// this is the pin for S2 on the color sensor
int S3 = 5; // this is the pin for S3 on the color sensor
int sensorOut = 11;// this is the pin for the OUT pin on the color sensor. 

int buttonPin = 2;//this is the pin that will read the status of the button.

int red = 0; // these are the variables that will store the reading from the color sensor
int green = 0;
int blue = 0;

bool greenTrack = false;//this will track if green is present or not. 



Servo myservo;  // create servo object to control a servo

// twelve servo objects can be created on most boards


//These are the variables for the vibration sensor
long measurement = 0;//This will be used to store the value of the vibration

bool reset = false;//this is a flag that will be used to signal a reset command
int turningDelays = 0; //This is a variable where the amount of turning delays will be triggered
int buttonState = 0;//this is a temporary button variable that will store the reading

void setup() {
  //set the output pins for the color sensor
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  //set the sensorOut as an input for the color sensor
  pinMode(sensorOut, INPUT);

  //set the frequency scaling to 20%. This is a proprietary setting in the sensor, 
  //where high/low is 20%. Freqency scaling is synonomus with sensitivity
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  //set the pin for the reset button
  pinMode(buttonPin, INPUT);

  //Begin serial communication

  Serial.begin(9600);//this allows for the coder to review the inputs
  

 //This is the setup for the vibration sensor
 
 Serial.begin(9600);
 
 






  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  //this is the code for the button status
  buttonState = digitalRead(buttonPin);

  if (buttonState==HIGH) {
    reset=true;
    Serial.println("pressed");
  } else {
    reset=false;
    Serial.println("not pressed");
    Serial.print(buttonState);
  }

  
  if (!reset) {
  //The below code is fo reading the color sensor.
  
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  //The sensor is now set to read RED. 

  red = pulseIn(sensorOut, LOW);//get red
  red = map(red, 255, 675, 255, 0);
  //Serial.print("R = ");//print it so the human can read it!
  //Serial.print(red);
  delay(100);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  //the sensor is now set to read green

  green = pulseIn(sensorOut, LOW);//get the green
  green = map(green, 550, 1187, 255, 0);
 // Serial.print("G = ");//print the green
 // Serial.print(green);
  delay(100);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH); 
  //the sensor is now set to read blue

  blue = pulseIn(sensorOut, LOW); //get the blue reading
  blue = map(blue, 270, 1220, 255, 0);
 // Serial.print(" B = ");
 // Serial.print(blue);
 // Serial.print("\n");
  delay(100);

  if(green>200) {
    greenTrack=true;//this says that there is green present
  } else {
    greenTrack=false;//this says that there isn't any green present
  }

  //print the blue reading




  if (greenTrack && turningDelays<220) {
    myservo.write(180);///starting moving
    delay(220);//this was a lot of trial and error. Now that the delay is set this way, it will turn in 90 degree increments
    myservo.write(90);//stop moving
    turningDelays+=220;
  } else {
    myservo.write(90);//stop moving
  }
  delay(300);//delay until the next cycle
  }
  else {
    //This means we will begin a reset command
    if (turningDelays>0) {
       myservo.write(0);//this will make it move in the opposite direction at the same theoretical velocity
        delay(turningDelays-10);
        myservo.write(90);//stop moving the servos.
        turningDelays=0;
    }

    greenTrack=false;
    //make sure to set reset to false upon the release of the button.
  }
  
}
