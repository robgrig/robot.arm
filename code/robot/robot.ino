#include "Joint.h"
#include <Servo.h>
int pos = 0;

#define MOVE_WRIST 0
#define MOVE_ARM 1
#define WAIT 2

int robot_state=MOVE_WRIST;

Joint shoulder(4,5,6,400,15); // PUL_pin_, DIR_pin_, ENA_pin_, motorDelayTime in microsecconds accordingly
Joint elbow(7,8,9,200,14); // PUL_pin_, DIR_pin_, ENA_pin_, motorDelayTime, Ending Pin in microsecconds accordingly
Joint base(1,2,3,200,16);
Joint planet(10,11,12,200,17);

Servo wristServo;

void close() {
	for (int servo_position =0  ; servo_position <=200; servo_position +=1){
		wristServo.write(servo_position);
		delay(15);
	}
}

void open() {
	for (int servo_position=200; servo_position >=0; servo_position -=1){
		wristServo.write(servo_position);
		delay(15);
	}
}

void setup()
{
    /*
    // for debugging
    Serial.begin(9600);
    pinMode(14, INPUT_PULLUP);
    while(true) {
      delay(10);
      Serial.println(digitalRead(14));
    }
    */
 

    wristServo.attach(44);
    open();
    delay(100);



    shoulder.calibrate();
    
    elbow.calibrate();
    delay(100);

    elbow.n_stepClockWise(2900);

    shoulder.n_stepClockWise(16000);

    close();
    delay(500);

//    elbow.n_stepAntiClockWise(100);

    shoulder.n_stepAntiClockWise(10000);
    base.n_stepClockWise(20000);
    delay(100);

        planet.n_stepClockWise(5000);

//    elbow.n_stepClockWise(100);

    shoulder.n_stepClockWise(5000);
//    base.n_stepClockWise(20000);

    open();
    shoulder.n_stepAntiClockWise(10000);
    base.n_stepClockWise(20000);
    delay(10000);
}
void loop()
{
    switch (robot_state) {
        case MOVE_WRIST:
            /*
             * generating PWM signal for the servo
             * 1100 means its in the minimum possition, in this case its closed
             * 1900 means its in the maximum position, in this cas its opened
             * you can also write from [1100,1900]
             */

            robot_state=WAIT; // changing the state
            break;

        case MOVE_ARM:
            elbow.n_stepAntiClockWise(1000);
            elbow.n_stepClockWise(1000);
            delay(100);
            // shoulder->n_stepAntiClockWise(1000);
            // shoulder->n_stepClockWise(1000);

            robot_state=WAIT;
            break;

        case WAIT:
            delay(10);
            break;
    }
}
