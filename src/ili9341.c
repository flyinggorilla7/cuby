//ili9341 Driver Source
#include <stdint.h>
#include "timer.h"
#include "ili9341.h"
#include "uart.h"
#include "tm4c123gh6pm.h"
#include "spi.h"

#define GPIO_RESET (1U << 4)
#define GPIO_DC (1U << 0)

void ili9341_init(){
	//Start with a hardware reset
	GPIO_PORTE_DATA_R ^= GPIO_RESET;
	timer_delay(10);
	GPIO_PORTE_DATA_R ^= GPIO_RESET;
	timer_delay(150);
	//Software Reset
	ili9341_write_command(0x01);
	timer_delay(150);

	//display on command
	ili9341_write_command(0x29);
	
	printString("ili9341 Initialized\n\r");
}





void ili9341_write_data(unsigned int data){
	//Set DC bit high to send data value
	GPIO_PORTE_DATA_R |= GPIO_DC;
	spi_send(data);
}



void ili9341_write_command(unsigned int command){
	//Set DC bit low to send command value
	GPIO_PORTE_DATA_R &= ~GPIO_DC;
	spi_send(command);

}
