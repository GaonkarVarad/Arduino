//Servo Motor
#include <Servo.h>
Servo myservo;
int servo_pin = A2; //A2 
int pos = 0;

//ultra sonic sensor
int echo = 10; //D10
int trigger = 9; //D9
int long mytime = 0; 
int distance = 0;

//IR sensor
int ir_pin = A5;//A5
int value = 0;


// Motor driver pins 
int INA = 5;//D5
int IN1 = 4;//D4
int IN2 = 2;//D2
int IN3 = 7;//D7
int IN4 = 8;//D8
int INB = 6;//D6

unsigned long turntime = 0;
float speedleft =0.0;
int speedpin = 11;//D11
int travel = 0;

unsigned long turntime_2 = 0;
float speedleft_2 =0.0;
int speedpin_2 = 12;//D12
int travel_1 = 0;

void setup() {
 Serial.begin(9600);
  
  pinMode(INA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(echo, INPUT); 
  pinMode(trigger, OUTPUT);
  pinMode(speedpin, INPUT);
  pinMode(speedpin_2, INPUT);
  pinMode (ir_pin, INPUT);
  myservo.write(60);
  myservo.attach(servo_pin);
}

void loop() {
// IR sensor 
value = digitalRead(ir_pin);
//Serial.println(value);

//Ultrasonic sensor
digitalWrite(trigger, LOW); delay(20); //short time to make sure no signal is sent
digitalWrite(trigger, HIGH); delay(100); //short time to make sure signal is sent
digitalWrite(trigger, LOW); //turn of the signal

mytime = pulseIn(echo, HIGH); //measures time till a rising high signal is detected
distance = (mytime * 0.034) / 2;
//Serial.print("Distance: ");
//Serial.print(distance);
//Serial.println(" cm"); 

if (value == 0){   //IR sensor 
  if (distance <= 40){  //Ultrasonic sensor
    //stop
    digitalWrite(IN1, LOW);digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);digitalWrite(IN4, LOW);
    delay(1000);
    //lookUltrasonic
    for (pos = 0; pos <=120; pos += 120){ //Servo Position
      myservo.write(pos);
      delay(1000);
    }
      if (distance <= 40){
        //stop
        digitalWrite(IN1, LOW);digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);digitalWrite(IN4, LOW);
        delay(1000);
      }
      //lookUltrasonic
    for (pos = 0; pos <= 60; pos += 60){  //Servo Position
      myservo.write(pos);
      delay(1000);
    }
      if (distance <= 40){
        //stop
        digitalWrite(IN1, LOW);digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);digitalWrite(IN4, LOW);
        delay(1000);  
      }
    //go bavkward
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    analogWrite(INA, 180); analogWrite(INB, 180); 
    delay(300);
    //stop  
    digitalWrite(IN1, LOW);digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);digitalWrite(IN4, LOW);
    delay(1000);

    if (random(0, 2) == 0){
      //go left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      }else {
      //go right
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);  
      }

      delay(500);
    //stop
    digitalWrite(IN1, LOW);digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);digitalWrite(IN4, LOW);
    delay(700);
}else{
  // go forward
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(INA, 147); analogWrite(INB, 202.02);
    //RPM for motor 1
    turntime = pulseIn(speedpin, HIGH);
    speedleft = 60/((20*float(turntime))/10000);
    Serial.println(speedleft);
    Serial.print("RPM_1");
    //RPM for motor 2
    turntime_2 = pulseIn(speedpin_2, HIGH);
    speedleft_2 = 60/((20*float(turntime_2))/10000);
    Serial.println(speedleft_2);
    Serial.print("RPM_2");
}
}else {
    //go forward
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(INA, 152); analogWrite(INB, 201);
}

}