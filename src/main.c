#include <stdbool.h>
#include <stdint.h>

#include "uart.h"
#include "tm4c123gh6pm.h"


#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3



int main()
{
	int volatile counter = 0;
	uart_init();
	for(;;){
		while(counter<10000000){
			counter++;
		}
		printString("My Gym Partner Is A Monkey\n\r");
	}

}
