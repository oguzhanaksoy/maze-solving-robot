
#include <AFMotor.h>
 
AF_DCMotor motor1(3, MOTOR12_64KHZ); //Left Motor
AF_DCMotor motor2(4, MOTOR12_64KHZ); //Right Motor


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
 motor1.setSpeed(255); 
 motor2.setSpeed(249);
    Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(trigPin2,OUTPUT);
delay(2000);
}

int sagSensor,solSensor,onSensor;
void loop()
{
 
      sagSensor = mesafeOlc(echoPin,trigPin);
      solSensor = mesafeOlc(echoPin1,trigPin1);
      onSensor = mesafeOlc(echoPin2,trigPin2);
  
     if(onSensor <= 15){
    if(sagSensor >= 15){
      sifirla(1); 
      sagaDon(850);
    }else if(solSensor >= 15){
      sifirla(0); 
      solaDon(850);
    }else{
      sifirla(0);
       solaDon(1700);
    }
  }else{
    ileri();
  }
     

     delay(250);
}

long microsaniyeSure, cmMesafe; // Mesafe hesabında kullanılan değişkenler
int c=0;
long mesafeOlc(int echo,int trig){
 digitalWrite(trig, LOW); // Hoparlör 2ms sessiz
 delayMicroseconds(2); 
 digitalWrite(trig, HIGH); // Hoparlör 10ms sesli
 delayMicroseconds(10); 
 digitalWrite(trig, LOW); // Hoparlör sessiz
 microsaniyeSure = pulseIn(echo, HIGH); // Mikrofonu dinle, yansıma süresini microsaniyeSure değişkenine al
 cmMesafe = microsaniyeSure/58.2; // microsaniyeSure'dan cm olarak mesafeyi hesapla
return cmMesafe;
}

void sol(bool yon)
{
  if(yon)
    motor1.run(FORWARD);
  else
    motor1.run(BACKWARD);

}

void sifirla(int saniye)
{
motor1.run(RELEASE);
motor2.run(RELEASE);
delay(saniye);
}

void sag(bool yon)
{
  if(yon)
    motor2.run(FORWARD);
  else
    motor2.run(BACKWARD);

}

void ileri()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    
}

 
void solaDon(int saniye){
  sag(true);
  sol(false);
     delay(saniye);
     sifirla(100);
}

void sagaDon(int saniye)
{
  sol(true);
  sag(false);
  delay(saniye);
  sifirla(100);
}



