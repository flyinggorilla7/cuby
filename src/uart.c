#include <stdbool.h>
#include <stdint.h>

#include "uart.h"
#include "tm4c123gh6pm.h"

void uart_init(){

	//Step 1
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	//Step 2
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	//Step 3
	GPIO_PORTA_AFSEL_R = (1U << 1) | (1U << 0);
	//Step 4 Configure GPIO Current/Slew Rate
	
	//Step 5 Configure PMCn fields
	GPIO_PORTA_PCTL_R = (1U << 4) | (1U << 0);

	GPIO_PORTA_DEN_R = (1U << 1) | (1U << 0);

	UART0_CTL_R &= ~(1U << 0);
		
	UART0_IBRD_R = 104;

	UART0_FBRD_R = 11;
	//8 bits, one stop bit
	UART0_LCRH_R = (0x3 << 5);
	//Use System Clock
	UART0_CC_R = 0x0;
	//Enable UART
	UART0_CTL_R |= (1U << 0) | (1U << 8) | (1U << 9);
}

void printString(char * string){
	
	while(*string != '\0'){
		printChar(*string);
		string++;
	}

}

void printChar(char alpha){
	
	while((UART0_FR_R & (1U << 5)) != 0U);
	UART0_DR_R = alpha;

}
