
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

bool sensor1;
bool sensor2;
bool sensor3;
bool sensor4;
bool sensor5;
bool sensor6;

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

void forwardRobot()
{
  motors.setSpeeds(200, 200);
  Serial.write("Forward");
}

/************************************************************************************************************************left************************************************/
void left90Robot()
{
  motors.setSpeeds(300, -100);
 Serial.write("Left 90");
}

void left75Robot()
{
    motors.setSpeeds(200, 0);
    Serial.write("left 75");
}

void left50Robot()
{
    motors.setSpeeds(200, 50);
    Serial.write("Left 50");
}

void left25Robot()
{
    motors.setSpeeds(200, 100);
    Serial.write("left 25");
}
void left5Robot()
{
    motors.setSpeeds(200,150);
    Serial.write("left 5");
}
/***********************************************************************************************************************right************************************************/
void right90Robot()
{
  motors.setSpeeds(-100, 300);
 Serial.write("right 90");
}

void right75Robot()
{
    motors.setSpeeds(0, 200);
    Serial.write("right 75");
}

void right50Robot()
{
    motors.setSpeeds(50, 200);
    Serial.write("right 50");
}

void right25Robot()
{
    motors.setSpeeds(100, 200);
    Serial.write("right 25");
}
void right5Robot()
{
    motors.setSpeeds(150,200);
    Serial.write("right 5");
}

void stopit()
{
      if(sensor1 && sensor2 && sensor3 && sensor4 && sensor5 && sensor6)
      {
      state = 0;
      }
}

void forward()
{

    if(!sensor1 && !sensor2 && sensor3 && sensor4 && !sensor5 && !sensor6)     // Move Forward
    {
       state = 1;
    }
}
/************************************************************************************************************************left************************************************/
void left90()
{
  if( !sensor1 && !sensor2 && !sensor3 && !sensor4 && !sensor5 && sensor6)
      {
        state = 2;
      }
}

void left75()
{
  if(!sensor1 && !sensor2 && !sensor3 && !sensor4 && sensor5 && sensor6)
  {
    state = 3;
  }
}

void left50()
{
  if(!sensor1 && !sensor2 && !sensor3 && !sensor4 && sensor5 && !sensor6)
  {
    state = 4;
  }
}

void left25()
{
  if(!sensor1 && !sensor2 && !sensor3 && sensor4 && sensor5 && !sensor6)
  {
    state = 5;
  }
}
void left5()
{
  if(!sensor1 && !sensor2 && !sensor3 && sensor4 && !sensor5 && !sensor6)
  {
    state = 6;
  }
}
/***********************************************************************************************************************right************************************************/

void right90()
{
  if( sensor1 && !sensor2 && !sensor3 && !sensor4 && !sensor5 && !sensor6)
      {
        state = 7;
      }
}

void right75()
{
  if(sensor1 && sensor2 && !sensor3 && !sensor4 && !sensor5 && !sensor6)
  {
    state = 8;
  }
}

void right50()
{
  if(!sensor1 && sensor2 && !sensor3 && !sensor4 && !sensor5 && !sensor6)
  {
    state = 9;
  }
}

void right25()
{
  if(!sensor1 && sensor2 && sensor3 && !sensor4 && !sensor5 && !sensor6)
  {
    state = 10;
  }
}
void right5()
{
  if(!sensor1 && !sensor2 && sensor3 && !sensor4 && !sensor5 && !sensor6)
  {
    state = 11;
  }
}

void loop(){
  sensors.read(sensor_values);
  //actions();
 
sensor1 = sensor_values[0] >  QTR_THRESHOLD;
sensor2 = sensor_values[1] >  QTR_THRESHOLD;
sensor3 = sensor_values[2] >  QTR_THRESHOLD;
sensor4 = sensor_values[3] >  QTR_THRESHOLD;
sensor5 = sensor_values[4] >  QTR_THRESHOLD;
sensor6 = sensor_values[5] >  QTR_THRESHOLD;

/*
 * State selection
 */
 


switch(state)
{
  case 0 :            //stop case
    stopRobot();
    forward();
    left90();
    left75();
    left50();
    left25();
    left5();
    right90();
    right75();
    right50();
    right25();
    right5(); 
  break;
  case 1 :            //forward case
    forwardRobot();
    stopit();
    left90();
    left75();
    left50();
    left25();
    left5();
    right90();
    right75();
    right50();
    right25();
    right5(); 
      
  break;  
  case 2 :            //left case
    left90Robot();
    stopit();
    forward();
    left75();
    left50();
    left25();
    left5();
    right90();
    right75();
    right50();
    right25();
    right5(); ;
      
  break;
  case 3 :
     left75Robot();
     stopit();
    forward();
    left90();
    left50();
    left25();
    left5();
    right90();
    right75();
    right50();
    right25();
    right5(); 
  break;
  case 4 :
      left50Robot();
      stopit();
    forward();
    left90();
    left75();
    left25();
    left5();
    right90();
    right75();
    right50();
    right25();
    right5(); 
  break;
  case 5 :
      left25Robot();
      stopit();
    forward();
    left90();
    left75();
    left50();
    left5();
    right90();
    right75();
    right50();
    right25();
    right5(); 
  break;
  case 6:
      left5Robot();
      stopit();
    forward();
    left90();
    left75();
    left50();
    left25();
    right90();
    right75();
    right50();
    right25();
    right5(); 
  break;    
  case 7 :            //right case
    right90Robot();
    stopit();
    forward();
    left90();
    left75();
    left50();
    left25();
    left5();
    right75();
    right50();
    right25();
    right5(); 
  break;
  case 8 :
      right75Robot();
      stopit();
    forward();
    left90();
    left75();
    left50();
    left25();
    left5();
    right90();
    right50();
    right25();
    right5(); 
  break;
  case 9:
      right50Robot();
      stopit();
    forward();
    left90();
    left75();
    left50();
    left25();
    left5();
    right90();
    right75();
    right25();
    right5(); 
  break;
  case 10:
      right25Robot();
      stopit();
    forward();
    left90();
    left75();
    left50();
    left25();
    left5();
    right90();
    right75();
    right50();
    right5(); 
  break;
  case 11:
      right5Robot();
      stopit();
    forward();
    left90();
    left75();
    left50();
    left25();
    left5();
    right90();
    right75();
    right50();
    right25();
  break;
 
  default:
  state = 0;
  break;  
}

  
}
