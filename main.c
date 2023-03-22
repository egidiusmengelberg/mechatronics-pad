#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

//global variables
bool linkLed = false;

// config

//led
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_NUM 2

//motor_l
#define MOTOR_L_DDR DDRB
#define MOTOR_L_PORT PORTB
#define MOTOR_L_NUM 2

//motor_r
#define MOTOR_R_DDR DDRB
#define MOTOR_R_PORT PORTB
#define MOTOR_R_NUM 2

//button_up
#define BUTTON_UP_DDR DDRB
#define BUTTON_UP_PORT PORTB
#define BUTTON_UP_PIN PINB
#define BUTTON_UP_NUM 2
//button_down
#define BUTTON_DOWN_DDR DDRB
#define BUTTON_DOWN_PORT PORTB
#define BUTTON_DOWN_PIN PINB
#define BUTTON_DOWN_NUM 2

//functions
void initMotor();
void moveMotor(bool direction);
void stopMotor();
void initButtons();
void initLed(void);
void ledOn(void);
void ledOff(void);

int main(void) {

	initMotor();
	initButtons();
	initLed();

    while(1) {}
}

void initMotor() {
    // set motor pins as outputs
    MOTOR_L_DDR |= (1 << MOTOR_L_NUM);
    MOTOR_R_DDR |= (1 << MOTOR_R_NUM);

    //turn off outputs
    MOTOR_L_PORT &= ~(1 << MOTOR_L_NUM);
    MOTOR_R_PORT &= ~(1 << MOTOR_R_NUM);
}

void moveMotor(bool direction) {
    switch (direction)
    {
		case true:
			MOTOR_L_PORT |= (1 << MOTOR_L_NUM);
			MOTOR_R_PORT &= ~(1 << MOTOR_R_NUM);
			break;
		case false:
			MOTOR_L_PORT &= ~(1 << MOTOR_L_NUM);
			MOTOR_R_PORT |= (1 << MOTOR_R_NUM);
			break;
		default:
			stopMotor();
			break;
    }
}

void stopMotor() {
    MOTOR_L_PORT |= (1 << MOTOR_L_NUM);
    MOTOR_R_PORT |= (1 << MOTOR_R_NUM);
}

void initButtons() {
    //button up
    BUTTON_UP_DDR &= ~(1 << BUTTON_UP_NUM);
    BUTTON_UP_PORT |= (1 << BUTTON_UP_NUM);

    //button down
    BUTTON_DOWN_DDR &= ~(1 << BUTTON_DOWN_NUM);
    BUTTON_DOWN_PORT |= (1 << BUTTON_DOWN_NUM);
}

void initLed(void) {
    LED_DDR |= (1 << LED_NUM);

    TCCR4A = 0;// set entire TCCR1A register to 0
    TCCR4B = 0;// same for TCCR1B
    TCNT4  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR4A = 15624/1;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR4B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR4B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK4 |= (1 << OCIE4A);

    sei();//allow interrupts
}

void ledOn(void) {
    linkLed = true;
}

void ledOff(void) {
    linkLed = false;
    LED_PORT &= ~(1 << LED_NUM);
}

ISR(TIMER4_COMPA_vect){
    if (linkLed) {
        LED_PORT ^= (1 << LED_NUM);
    }
}