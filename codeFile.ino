
#include <AFMotor.h>
 
AF_DCMotor engineL(3, MOTOR12_64KHZ); //Left Motor
AF_DCMotor engineR(4, MOTOR12_64KHZ); //Right Motor


//Right Sensor 
const int trigPin =2;
const int echoPin =9;


//Left Sensor
const int trigPin1 =10;
const int echoPin1 =13;

//Front Sensor
const int trigPin2 =A0;
const int echoPin2 =A1;


void setup() {
 engineL.setSpeed(255); 
 engineR.setSpeed(249);
    Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(trigPin2,OUTPUT);
delay(2000);
}

int sensorL,sensorR,sensorF;
void loop()
{
 
      sensorL = calculateDistance(echoPin,trigPin);
      sensorR = calculateDistance(echoPin1,trigPin1);
      sensorF = calculateDistance(echoPin2,trigPin2);
  
     if(sensorF <= 15){
    if(sensorR >= 15){
      clear(1); 
      turnR(850);
    }else if(sensorL >= 15){
      clear(0); 
      turnL(850);
    }else{
      clear(0);
       turnL(1700);
    }
  }else{
    forward();
  }
     

     delay(250);
}

long microSecondTime, cmDistance; // Variable for using calculate distance
int c=0;
long calculateDistance(int echo,int trig){
 digitalWrite(trig, LOW); // 2ms send 5v the Ultra Sonic Sensor
 delayMicroseconds(2); 
 digitalWrite(trig, HIGH); // 10ms send 0V(ground) the Ultra Sonic Sensor
 delayMicroseconds(10); 
 digitalWrite(trig, LOW); // send 0V(ground)
 microSecondTime = pulseIn(echo, HIGH); // Listen the micrphone of sensor and get the echo 
 cmDistance = microSecondTime/58.2; //Calculate the cm distance from @microSecondTime
return cmDistance;
}

void left(bool direction)
{
  if(direction)
    engineL.run(FORWARD);
  else
    engineL.run(BACKWARD);

}

void clear(int second)
{
	engineL.run(RELEASE);
	engineR.run(RELEASE);
	delay(second);
}

void right(bool direction)
{
  if(direction)
    engineR.run(FORWARD);
  else
    engineR.run(BACKWARD);

}

void forward()
{
    engineL.run(BACKWARD);
    engineR.run(BACKWARD);
    
}

 
void turnL(int second){
  right(true);
  left(false);
     delay(second);
     clear(100);
}

void turnR(int second)
{
  left(true);
  right(false);
  delay(second);
  clear(100);
}



