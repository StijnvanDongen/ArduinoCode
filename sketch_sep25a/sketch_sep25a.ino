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
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#define NUM_SENSORS 6
#define LED 13
#define QTR_THRESHOLD  1000

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 400;
int state=0;

unsigned int sensor_values[NUM_SENSORS];

void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);

  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(100);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(100);
}




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
  // by rotating in place to sweep the sensors over the line*/
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
  /*
  buzzer.play(">g32>>c32");
*/
  // Wait for the user button to be pressed and released
  button.waitForButton();
/*
  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());*/

  pinMode(LED, HIGH);

  waitForButtonAndCountDown();
  
  Serial.begin(9600);
}


void stopRobot()
{
  motors.setSpeeds(0, 0);
  Serial.write("Stop");
}

void turnLeftRobot()
{
  motors.setSpeeds(200, -200);
 Serial.write("TurnLeft");
}

void turnRightRobot()
{
  motors.setSpeeds(-200, 200);
 Serial.write("TurnRight");
}

void forwardRobot()
{
  motors.setSpeeds(200, 200);
  Serial.write("Forward");
}
/*
void caseFinding(){
  motors.setSpeeds(50, 200);
  Serial.write("caseFinding");
}
*/

void loop(){
  sensors.read(sensor_values);
  //actions();



/*
 * State selection
 */


switch(state)
{
  case 0 :
    stopRobot();
    if(sensor_values[0] < QTR_THRESHOLD && sensor_values[1] < QTR_THRESHOLD &&sensor_values[4] < QTR_THRESHOLD &&sensor_values[5] < QTR_THRESHOLD && sensor_values[2] > QTR_THRESHOLD && sensor_values[3] > QTR_THRESHOLD )     // Move Forward
    {
       state = 1;
    }
    if(sensor_values[5] > QTR_THRESHOLD)
      {
        state = 2;
      }
     if(sensor_values[0] > QTR_THRESHOLD)
      {
      state = 3;
      }
      if(sensor_values[0] < QTR_THRESHOLD && sensor_values[1] < QTR_THRESHOLD && sensor_values[2] < QTR_THRESHOLD && sensor_values[3] < QTR_THRESHOLD && sensor_values[4] < QTR_THRESHOLD && sensor_values[5] < QTR_THRESHOLD)
      {
        state = 4;
        }
  break;
  case 1 :
    forwardRobot();
    if(sensor_values[5] > QTR_THRESHOLD)
      {
        state = 2;
      }
     if(sensor_values[0] > QTR_THRESHOLD)
      {
      state = 3;
      }
      if(sensor_values[0] > QTR_THRESHOLD && sensor_values[1] > QTR_THRESHOLD && sensor_values[2] > QTR_THRESHOLD && sensor_values[3] > QTR_THRESHOLD && sensor_values[4] > QTR_THRESHOLD && sensor_values[5] > QTR_THRESHOLD)
      {
        state = 0;
        }
        if(sensor_values[0] < QTR_THRESHOLD && sensor_values[1] < QTR_THRESHOLD && sensor_values[2] < QTR_THRESHOLD && sensor_values[3] < QTR_THRESHOLD && sensor_values[4] < QTR_THRESHOLD && sensor_values[5] < QTR_THRESHOLD)
      {
        state = 4;
        }
  break;  
  case 2 :
    turnLeftRobot();
    if(sensor_values[2] > QTR_THRESHOLD && sensor_values[3] > QTR_THRESHOLD)     // Move Forward
    {
       state = 1;
    }
    if(sensor_values[0] < QTR_THRESHOLD && sensor_values[1] < QTR_THRESHOLD && sensor_values[2] < QTR_THRESHOLD && sensor_values[3] < QTR_THRESHOLD && sensor_values[4] < QTR_THRESHOLD && sensor_values[5] < QTR_THRESHOLD)
      {
        state = 4;
        }
      
  break;
  case 3 :
    turnRightRobot();
    if(sensor_values[2] > QTR_THRESHOLD && sensor_values[3] > QTR_THRESHOLD)     // Move Forward
    {
       state = 1;
    }
    if(sensor_values[0] < QTR_THRESHOLD && sensor_values[1] < QTR_THRESHOLD && sensor_values[2] < QTR_THRESHOLD && sensor_values[3] < QTR_THRESHOLD && sensor_values[4] < QTR_THRESHOLD && sensor_values[5] < QTR_THRESHOLD)
      {
        state = 4;
        }
  break;
 /* case 4 :
  caseFinding();
  if(sensor_values[5] > QTR_THRESHOLD)
      {
        state = 2;
      }
     if(sensor_values[0] > QTR_THRESHOLD)
      {
      state = 3;
      }
      if(sensor_values[0] > QTR_THRESHOLD && sensor_values[1] > QTR_THRESHOLD && sensor_values[2] > QTR_THRESHOLD && sensor_values[3] > QTR_THRESHOLD && sensor_values[4] > QTR_THRESHOLD && sensor_values[5] > QTR_THRESHOLD)
      {
        state = 0;
        }
        if(sensor_values[0] < QTR_THRESHOLD && sensor_values[1] < QTR_THRESHOLD &&sensor_values[4] < QTR_THRESHOLD &&sensor_values[5] < QTR_THRESHOLD && sensor_values[2] > QTR_THRESHOLD && sensor_values[3] > QTR_THRESHOLD )     // Move Forward
    {
       state = 1;
    }
  break;
  */
  default:
  state = 0;
  break;  
}

  
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
