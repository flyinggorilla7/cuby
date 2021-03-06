#include <stdbool.h>
#include <stdint.h>

#include "uart.h"
#include "tm4c123gh6pm.h"
#include "timer.h"
#include "spi.h"
#include "ili9341.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

#define GPIO_CS (1U << 5)
#define GPIO_RESET (1U << 4)
#define GPIO_DC (1U << 0)

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

//PE0 and PE4 are used for this project
void gpio_porte_init(){
	//Enable clock gating to port e
	SYSCTL_RCGCGPIO_R |= (1U << 4);
	
	//Enable AHB
	SYSCTL_GPIOHBCTL_R |= (1U << 4);
	//Set direction to output
	GPIO_PORTE_AHB_DIR_R |= GPIO_CS | GPIO_DC | GPIO_RESET;
	//Reset Pin should be pulled high
	//GPIO_PORTE_AHB_PUR_R |= GPIO_DC;
	//Make sure Pull down and open drain are disabled	
	//GPIO_PORTE_AHB_PDR_R &= ~GPIO_DC;
	//GPIO_PORTE_AHB_ODR_R &= ~GPIO_DC;
	//Enable as outputs
	GPIO_PORTE_AHB_DEN_R |= GPIO_CS | GPIO_DC | GPIO_RESET;
	GPIO_PORTE_AHB_DATA_R |= GPIO_CS | GPIO_DC | GPIO_RESET;
}

int main()
{
	led_init();
	gpio_porte_init();
	timer_init();
	uart_init();
	printString("UART Initialized\n\r");
	spi_init();
	ili9341_init();
	printString("ILI9341 Initialized\n\r");
	int volatile counter = 0;
	while(1){
		GPIO_PORTF_DATA_R ^= LED_RED;
		timer_delay(1000);
		printString("Monkey\n\r");
	}
	/*for(;;){
		for(counter = 0; counter < 1000000; counter++);
		GPIO_PORTF_DATA_R ^= LED_RED;
		printString("My Gym Partner Is A Monkey\n\r");
	}*/

}
