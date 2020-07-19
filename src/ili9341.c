//ili9341 Driver Source
#include <stdint.h>
#include "timer.h"
#include "ili9341.h"
#include "uart.h"
#include "tm4c123gh6pm.h"
#include "spi.h"

#define GPIO_PORT_E GPIO_PORTE_AHB_DATA_R
#define GPIO_CS (1U << 5)
#define GPIO_RESET (1U << 4)
#define GPIO_DC (1U << 0)

void ili9341_init(){
	//Start with a hardware reset
	GPIO_PORTE_AHB_DATA_R &= ~GPIO_RESET;
	timer_delay(10);
	GPIO_PORTE_AHB_DATA_R |= GPIO_RESET;
	timer_delay(150);

	//Software Reset
	ili9341_write_command(0x01);
	timer_delay(150);
	
	//Pixel Format Display
	//Set to 16bit/pixel
	ili9341_write_command(0x3A);
	ili9341_write_data(0x55);
	
	//Interface Control
	ili9341_write_command(0xF6);
	GPIO_PORT_E &= ~GPIO_CS;
	ili9341_write_bytes(0x00);
	ili9341_write_bytes(0x00);
	ili9341_write_bytes(0x00);
	
	GPIO_PORT_E |= GPIO_CS;

	//Exit Sleep
	ili9341_write_command(0x11);
	timer_delay(150);

	//display on command
	ili9341_write_command(0x29);
}

//Use this when you need to send multiple parameters over
//the same active low chip select
void ili9341_write_bytes(unsigned int data){
	GPIO_PORT_E |= GPIO_DC;
	spi_send(data);
	timer_delay_us(13);
}



void ili9341_write_data(unsigned int data){
	//Set DC bit high to send data value
	GPIO_PORT_E |= GPIO_DC;
	GPIO_PORT_E &= ~GPIO_CS;
	spi_send(data);
	timer_delay_us(13);
	GPIO_PORT_E |= GPIO_CS;
}



void ili9341_write_command(unsigned int command){
	//Set DC bit low to send command value
	GPIO_PORT_E &= ~GPIO_DC;
	GPIO_PORT_E &= ~GPIO_CS;
	spi_send(command);
	timer_delay_us(13);
	GPIO_PORT_E |= GPIO_CS;
}
