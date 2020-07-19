//Timer Initialization
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "timer.h"
#include "uart.h"

void timer_init(){
	//Init for 32 bit timer
	//Enable timer 0 bit
	SYSCTL_RCGCWTIMER_R |= (1U << 0);
	//Clear timer a enable bit
	WTIMER0_CTL_R &= ~(1U << 0);
	//Write 4 to CFG register
	//this selects the 32 bit mode
	WTIMER0_CFG_R = 0x00000004;
	//Set timer a to one-shot mode
	WTIMER0_TAMR_R |= (1U << 0);
	//Set prescaler to value of 16000
	WTIMER0_TAPR_R = 0x00003E80;

	SYSCTL_RCGCTIMER_R |= (1U << 0);
	TIMER0_CTL_R &= ~(1U << 0);
	TIMER0_CFG_R = 0x0;
	TIMER0_TAMR_R |= (1U << 0);
	//Set prescalar to value of 16
	TIMER0_TAPR_R = 0x10;	
}

//duration - desired time in ms
void timer_delay(unsigned int duration){
	//PIOSC is 16MHz. Prescalar value of 16,000
	//1ms per clock cycle
	//Load timer value
	WTIMER0_TAILR_R = duration;
	//Enable time-out interrupt
	//WTIMER0_MIS_R = (1U << 0);
	//Enable timer a
	WTIMER0_CTL_R |= (1U << 0);
	
	//RIS is the raw interrupt status register
	//Wait until timer complete flag is 1
	while((WTIMER0_RIS_R & (1U << 0)) != 1);
	//Clear timer complete flag
	WTIMER0_ICR_R |= (1U << 0);
	//Clear timer a enable bit
	WTIMER0_CTL_R &= ~(1U << 0);

}

void timer_delay_us(unsigned int duration){
	//Prescalar value of 16
	//1us per clock cycle
	TIMER0_TAILR_R = duration;
	TIMER0_CTL_R |= (1U << 0);	
	while((TIMER0_RIS_R & (1U << 0)) != 1);
	TIMER0_ICR_R |= (1U << 0);
	TIMER0_CTL_R &= ~(1U << 0);
}















