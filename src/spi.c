#include "spi.h"
#include "tm4c123gh6pm.h"

//SPI Source File

void init_spi(){
	//Enable SSI Module 0
	SYSCTL_RCGCSSI_R |= (1U << 0);
	//Enable GPIO Port A
	SYSCTL_RCGCGPIO_R |= (1U << 0);	
	//Enable Alternate Function of GPIO Pins
	GPIO_PORTA_AFSEL_R |= (1U << 5) | (1U << 4) | (1U << 3) | (1U << 2);
	//Select SSI As Alternate Function of GPIO Pins
	GPIO_PORTA_PCTL_R |=	GPIO_PCTL_PA2_SSI0CLK |	
				GPIO_PCTL_PA3_SSI0FSS |
				GPIO_PCTL_PA4_SSI0RX  |
				GPIO_PCTL_PA5_SSI0TX;
	//GPIO Digital Enable
	GPIO_PORTA_DEN_R |= (1U << 5) | (1U << 4) | (1U << 3) | (1U << 2);
	
	//Look into Pullups/Pulldowns!!!
	
	//Configure SSI
	//Step 1 Clear SSE Bit in SSICR1 Register
	SSI0_CR1_R &= ~(1U << 1);
	//Step 2 Select Master or Slave Operation
	SSI0_CR1_R = 0x0;
	//Step 3 Configure SSI Clock Source by writing to the SSICC Register
	SSI0_CC_R = 0x0;
	//Step 4 Configure clock prescaler by writing to SSI0_CPSR_R
	SSI0_CPSR_R = 0x4;
	//Step 5 Configure SSI0_CR0 Register
	//Configured with SPH, SPO, and FRF at 0
	SSI0_CR0_R = (7U << 0) | (1U << 8);  	
	//Enable SSI0
	SSI0_CR1_R |= (1U << 1);
	
}
