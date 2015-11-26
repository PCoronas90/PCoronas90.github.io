#include <Servo.h>     //Inclue Servo Library 
#include <NewPing.h>   //Include NewPing Library

Servo leftServo;       //Create Left Servo object
Servo rightServo;      //Create Right Servo object

#define TRIGGER_PIN  8   //Trigger pin of Ultrasonic sensor connected to pin 6
#define ECHO_PIN     9   //Echo pin of Ultrasonic sensor connected to pin 7
#define MAX_DISTANCE 100 //The maximum distance we want the sensor to look for is 1m

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //Create Ultrasonic sensor object

unsigned int time;            //Variable to store how long it takes for the ultrasonic wave to come back
int distance;                 //Variable to store the distance calculated from the sensor
 int triggerDistance = 30;     //The distance we want the robot to look for a new path
int fDistance;                //Variable to store the distance in front of the robot
int lDistance;                //Variable to store the distance on the left side of the robot
int rDistance;                //Variable to store the distance on the right side of the robot

void setup() 
{ 
  leftServo.attach(11);        //Left servo connected to pin 9
  leftServo.write(90);        //Write the neutral position to that servo
  rightServo.attach(10);       //Right servo connected to pin 8
  rightServo.write(90);       //Write the neutral position to that servo
} 

void loop()
{
  scan();                                //Get the distance retrieved
  fDistance = distance;                  //Set that distance to the front distance
  if(fDistance < triggerDistance){       //If there is something closer than 30cm in front of us
    moveBackward();                      //Move Backward for a second
    delay(1000); 
    moveRight();                         //Turn Right for half a second
    delay(500);
    moveStop();                          //Stop
    scan();                              //Take a reading
    rDistance = distance;                //Store that to the distance on the right side
    moveLeft();
    delay(1000);                         //Turn left for a second
    moveStop();                          //Stop
    scan();                              //Take a reading
    lDistance = distance;                //Store that to the distance on the left side
    if(lDistance < rDistance){           //If the distance on the left is smaller than that of the right
      moveRight();                       //Move right for a second
      delay(1000);
      moveForward();                     //Then move forward
    }
    else{
      moveForward();                     //If the left side is larger than the right side move forward
    }
  }
  else{
    moveForward();                       //If there is nothing infront of the robot move forward
  }
}

void scan(){
  time = sonar.ping();                  //Send out a ping and store the time it took for it to come back in the time variable
  distance = time / US_ROUNDTRIP_CM;    //Convert that time into a distance
  if(distance == 0){                    //If no ping was recieved
    distance = 100;                     //Set the distance to max
  }
  delay(10);
}

void moveBackward(){
  rightServo.write(0);
  leftServo.write(180); 
}

void moveForward(){
  rightServo.write(180);
  leftServo.write(0);
}

void moveRight(){
  rightServo.write(0);
  leftServo.write(0);  
}

void moveLeft(){
  rightServo.write(180);
  leftServo.write(180);
}

void moveStop(){
  rightServo.write(90);
  leftServo.write(95); 
}


