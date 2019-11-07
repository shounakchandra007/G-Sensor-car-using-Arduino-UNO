//Code is written by @Shounak Chandra
#define REMOTEXY_MODE__SOFTWARESERIAL  
#include <SoftwareSerial.h>             //Including the software serial library
#include <RemoteXY.h>                   //Including the remotexy library

/* RemoteXY connection settings */ 
#define REMOTEXY_SERIAL_RX 2            //defining the pin 2 as RX pin
#define REMOTEXY_SERIAL_TX 3            //defining the pin 3 as TX pin
#define REMOTEXY_SERIAL_SPEED 9600      //setting baudrate at 9600

unsigned char RemoteXY_CONF[] =       //remotexy configuration
  { 3,0,23,0,1,5,5,15,41,11 
  ,43,43,1,2,0,6,5,27,11,5 
  ,79,78,0,79,70,70,0 };  
    
struct {                            //Function for declaring the variables
  signed char joystick_1_x;         //joystick x-axis 
  signed char joystick_1_y;         //joystick y-axis
  unsigned char switch_1;           //variables for switch
  unsigned char connect_flag; 

} RemoteXY;  

//defining the pins for first motor
#define IN1 10 
#define IN2 9 
#define ENA 12 

//defining the pins for second motor
#define IN3 8 
#define IN4 7 
#define ENB 11 

//defining the LED pin  
#define ledpin 13 

unsigned char first_motor[3] =  
  {IN1, IN2, ENA}; 
unsigned char second_motor[3] =  
  {IN3, IN4, ENB}; 

void Speed (unsigned char * pointer, int motor_speed) 
{ 
  if (motor_speed>100) motor_speed=100; 
  if (motor_speed<-100) motor_speed=-100; 
  if (motor_speed>0) { 
    digitalWrite(pointer[0], HIGH); 
    digitalWrite(pointer[1], LOW); 
    analogWrite(pointer[2], motor_speed*2.55); 
  } 
  else if (motor_speed<0) { 
    digitalWrite(pointer[0], LOW); 
    digitalWrite(pointer[1], HIGH); 
    analogWrite(pointer[2], (-motor_speed)*2.55); 
  } 
  else { 
    digitalWrite(pointer[0], LOW); 
    digitalWrite(pointer[1], LOW); 
    analogWrite(pointer[2], 0); 
  } 
} 

void setup() 
{ 
  //defining the motor pins as the output pins
  pinMode (IN1, OUTPUT); 
  pinMode (IN2, OUTPUT); 
  pinMode (IN3, OUTPUT); 
  pinMode (IN4, OUTPUT); 
  pinMode (ledpin, OUTPUT); 
  RemoteXY_Init (); 
} 

void loop() 
{ 
  RemoteXY_Handler (); 
  digitalWrite (ledpin, (RemoteXY.switch_1==0)?LOW:HIGH);  
  Speed (first_motor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x); 
  Speed (second_motor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x); 
} 
