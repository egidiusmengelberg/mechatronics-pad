#include <avr/io.h>
#include <avr/interrupt.h>

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

int main(void) {

    while(1) {}
}