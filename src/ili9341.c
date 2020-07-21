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

static unsigned int start_column;
static unsigned int end_column;
static unsigned int start_row;
static unsigned int end_row;


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
	/*ili9341_write_command(0xF6);
	GPIO_PORT_E &= ~GPIO_CS;
	ili9341_write_bytes(0x00);
	ili9341_write_bytes(0x00);
	ili9341_write_bytes(0x00);
	
	GPIO_PORT_E |= GPIO_CS;
	*/
	
	ili9341_set_columns(79U, 159U);
	ili9341_set_rows(100U,200U);


	//Exit Sleep
	ili9341_write_command(0x11);
	timer_delay(150);

	//display on command
	ili9341_write_command(0x29);
	timer_delay(150);
	/*
	//write colors
	ili9341_write_command(0x2C);
	GPIO_PORT_E &= ~GPIO_CS;
	for(int i = 0; i < 40000; i++){
		ili9341_write_data(0x07);
		ili9341_write_data(0xE0);
	}
	GPIO_PORT_E |= GPIO_CS;
	*/
	ili9341_outline_square();


}

//draws square frame at border of current row and column selection
void ili9341_outline_square(){
	
	
	unsigned int width = end_column - start_column;
	unsigned int height = end_row - start_row;
	
	ili9341_write_command(0x2C);
	GPIO_PORT_E &= ~GPIO_CS;

	for(int row = 0; row <= height; row++){
		for(int column = 0; column <= width; column++){
			if(row == 0 || row == (height - 1)){
				ili9341_write_data(0x07);
				ili9341_write_data(0xE0);
				continue;
			}
			if(column == 0 || column == (width -1)){
				ili9341_write_data(0x07);
				ili9341_write_data(0xE0);
				continue;
			}
			ili9341_write_data(0xFF);
			ili9341_write_data(0xFF);
		}
	}

	GPIO_PORT_E |= GPIO_CS;

}

//set start and end of rows
void ili9341_set_rows(unsigned int start, unsigned int end){
	ili9341_write_command(0x2B);
	GPIO_PORT_E &= ~GPIO_CS;
	//start
	ili9341_write_data((start & 0xFF00) >> 8);
	ili9341_write_data(start & 0x00FF);
	//end
	ili9341_write_data((end & 0xFF00) >> 8);
	ili9341_write_data(end & 0x00FF);
	
	GPIO_PORT_E |= GPIO_CS;
	start_row = start;
	end_row = end;	
}

//set start and end of columns
void ili9341_set_columns(unsigned int start, unsigned int end){
	ili9341_write_command(0x2A);
	GPIO_PORT_E &= ~GPIO_CS;
	//start
	ili9341_write_data((start & 0xFF00) >> 8);
	ili9341_write_data(start & 0x00FF);
	//end
	ili9341_write_data((end & 0xFF00) >> 8);
	ili9341_write_data(end & 0x00FF);
	
	GPIO_PORT_E |= GPIO_CS;	
	start_column = start;
	end_column = end;
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
