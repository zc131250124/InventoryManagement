#include <wiringPi.h>
#include <softPwm.h>

#ifndef GPIOLIB_H
#define GPIOLIB_H

#define FORWARD 1
#define BACKWARD 0


//Pins in control of the motor on the left
const int IN1=22;
const int IN2=23;
const int ENA=24;
//Pins in control of the motor on the right
const int IN3=27;
const int IN4=28;
const int ENB=29;

namespace GPIO
{
	int init(){
		//Call this function at the start of any program related GPIO on RPi.
		wiringPiSetup();
		//The only PWM output is used by servo, so we need soft PWM to control rotation speed of motors.
		softPwmCreate(ENA,0,100);
		softPwmCreate(ENB,0,100);

		pinMode(IN1,OUTPUT);
		pinMode(IN2,OUTPUT);
		pinMode(IN3,OUTPUT);
		pinMode(IN4,OUTPUT);
	}
	
	int controlLeft(int direction,int speed){
		if(direction==FORWARD){
			digitalWrite(IN1,HIGH);
			digitalWrite(IN2,LOW);
		}else if(direction==BACKWARD){
			digitalWrite(IN1,LOW);
			digitalWrite(IN2,HIGH);
		}
		
		softPwmWrite(ENA,speed);

	}
	int controlRight(int direction,int speed){
		if(direction==FORWARD){
			digitalWrite(IN3,HIGH);
			digitalWrite(IN4,LOW);
		}else if(direction==BACKWARD){
			digitalWrite(IN3,LOW);
			digitalWrite(IN4,HIGH);
		}
		softPwmWrite(ENB,speed);
	}

	int stopLeft(){
		softPwmWrite(ENA,0);
		digitalWrite(IN1,LOW);
		digitalWrite(IN2,LOW);
	}
	int stopRight(){
		softPwmWrite(ENB,0);
		digitalWrite(IN3,LOW);
		digitalWrite(IN4,LOW);
	}
	
	int resetCounter();
	void getCounter(int *countLeft,int *countRight);
	
	int turnTo(int angle);
	
	void delay(int milliseconds){
		delay(milliseconds);
	}
}
#endif
