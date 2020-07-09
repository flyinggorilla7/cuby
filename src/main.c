#include <stdbool.h>
#include <stdint.h>

#include "uart.h"
#include "tm4c123gh6pm.h"
#include "timer.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)


//PF1 Red PF2 Blue PF3 Green
//Initialize Debug LEDs
void led_init(){
	//Enable clock gating
	SYSCTL_RCGCGPIO_R |= (1U << 5);	
	//Set direction to output
	GPIO_PORTF_DIR_R |= LED_RED | LED_BLUE | LED_GREEN;
	//Enable as outputs
	GPIO_PORTF_DEN_R |= LED_RED | LED_BLUE | LED_GREEN;
		
}


int main()
{
	led_init();
	
	uart_init();
	timer_init();
	printString("Initialized\n\r");
	int volatile counter = 0;
	for(;;){
		for(counter = 0; counter < 1000000; counter++);
		GPIO_PORTF_DATA_R ^= LED_RED;
		printString("My Gym Partner Is A Monkey\n\r");
	}

}
