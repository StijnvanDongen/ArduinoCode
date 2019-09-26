/*
 * Demo line-following code for the Pololu Zumo Robot
 *
 * This code will follow a black line on a white background, using a
 * PID-based algorithm.  It works decently on courses with smooth, 6"
 * radius curves and has been tested with Zumos using 30:1 HP and
 * 75:1 HP motors.  Modifications might be required for it to work
 * well on different courses or with different motors.
 *
 * https://www.pololu.com/catalog/product/2506
 * https://www.pololu.com
 * https://forum.pololu.com
 */

#include <Wire.h>
#include <ZumoShield.h>

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 400;
int state=0;

void setup()
{
  /*
}
  // Play a little welcome song
  buzzer.play(">g32>>c32");

  // Initialize the reflectance sensors module
  reflectanceSensors.init();

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Turn on LED to indicate we are in calibration mode
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);

  // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);
  buzzer.play(">g32>>c32");

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());*/
  
  Serial.begin(9600);
}

void stopRobot()
{
  Serial.write("stoprobot");
}

void turnLeftRobot()
{
  Serial.write("turnleft");
 
}

void turnRightRobot()
{
  Serial.write("turnright");  
}

void forwardRobot()
{
  Serial.write("forward");  
}

void loop()
{


  readSensors();
  actions();
  button.waitForButton();
  


/*
 * State selection
 */
switch(state)
{
  case 0 :
    stopRobot();
  break;
  case 1 :
    forwardRobot();
  break;  
  case 2 :
    turnLeftRobot();
  break;
  case 3 :
    turnRightRobot();
  break;
  default:
  break;  
}
  button.waitForButton();
  state=1;
switch(state)
{
  case 0 :
    stopRobot();
  break;
  case 1 :
    forwardRobot();
  break;  
  case 2 :
    turnLeftRobot();
  break;
  case 3 :
    turnRightRobot();
  break;
  default:
  break;   
}  
  button.waitForButton();
  state=2;

switch(state)
{
  case 0 :
    stopRobot();
  break;
  case 1 :
    forwardRobot();
  break;  
  case 2 :
    turnLeftRobot();
  break;
  case 3 :
    turnRightRobot();
  break;
  default:
  break;   
}
     button.waitForButton();
  state=3;
switch(state)
{
  case 0 :
    stopRobot();
  break;
  case 1 :
    forwardRobot();
  break;  
  case 2 :
    turnLeftRobot();
  break;
  case 3 :
    turnRightRobot();
  break;
  default:
  break; 
}
state=0;
}











/*

  
  if(sensor[2] && sensor[3]))     // Move Forward
  {
    motors.setSpeed(MAX_SPEED);
  }
  
  if(!(sensor[1]) && sensor[4])     // Turn right
  {
    
  }
  
  if(sensor[1] && !(sensor[4]))     // turn left
  {
    
  }
  
  if(!(sensors[6]))     // stop
  {
    motors.setSpeed(0);
  }*/
