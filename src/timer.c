//Timer Initialization
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "timer.h"
#include "uart.h"

void timer_init(){

	//Enable timer 0 bit
	SYSCTL_RCGCTIMER_R |= (1U << 0);
	//Clear timer a enable bit
	TIMER0_CTL_R &= ~(1U << 0);
	//Write 0 to CFG register
	TIMER0_CFG_R = 0x0;
	//Set timer a to one-shot mode
	TIMER0_TAMR_R = (1U << 0);
	//Set prescaler
	TIMER0_TAPR_R = ~0;	
}

//duration - desired time in ms, must be less than 200
void timer_delay(unsigned int duration){
	//Clock speed set to 80MHz with prescaler of 255
	//Approximately 3188 nano seconds per clock cycle
	if(duration > 200){
		duration = 200;
	}
	//convert desired time to required clock cycles
	unsigned int clockCountValue = duration * 1000000 / 3188;
	//Load timer value
	TIMER0_TAILR_R = clockCountValue;
	//Enable time-out interrupt
	TIMER0_MIS_R = (1U << 0);
	//Enable timer a
	TIMER0_CTL_R |= (1U << 0);
}
