/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "stm8l10x.h"
#include "stm8l10x_gpio.h"

#ifdef _COSMIC_  
	#define ASM  _asm
#endif
#ifdef _IAR_  
	#define ASM  asm
#endif

/* This delay should be added just after reset to have 
access to SWIM pin    and to be able to reprogram the device
after power on (otherwise the    device will be locked) */
#define STARTUP_SWIM_DELAY_5S   \
{																\
	ASM("       PUSHW X        \n"\
	"       PUSH  A        \n"   	\
	"LDW X, #0xFFFF \n"   				\
	"loop1: LD  A, #50     \n"   	\
																\
	"loop2: DEC A          \n"   	\
	"       JRNE loop2     \n"   	\
																\
	"       DECW X         \n"   	\
	"       JRNE loop1     \n"   	\
																\
	"       POP  A         \n"   	\
	"       POPW X           " );	\
	}
	
/* unbonded pins as output low state (the best EMC immunity)
(PA1, PA3, PA5, PB0, PB1, PB2, PB4, PC5, PC6, PD1, PD2, PD3, PD4, PD5,
PD6, PD7)*/ 

#define CONFIG_UNUSED_PINS_STM8L001												\
{																													\
	GPIOA->DDR |= GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5;			\
	GPIOB->DDR |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |		\
								GPIO_Pin_4;																\
	GPIOC->DDR |= GPIO_Pin_5 | GPIO_Pin_6;									\
	GPIOD->DDR |= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |		\
								GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |		\
								GPIO_Pin_7;																\
}

void Set_FSKData(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

void Reset_FSKData(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

void Set_ASKData(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_2);
}

void Reset_ASKData(void)
{
	GPIO_ToggleBits(GPIOB, GPIO_Pin_7);
}

void Set_PWRDown(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void Reset_PWRDown(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void PLL_On(void)
{
	uint16_t i;
	Set_FSKData();
	Reset_ASKData();
	for(i=0;i<200;i++);
}

void PLL_Off(void)
{
	Reset_FSKData();
}

main()
{
	int16_t i;
	 /* -------------STM8L001 startup-------------- */
	 /* configure unbonded pins */
	 CONFIG_UNUSED_PINS_STM8L001;
	 /* delay for SWIM connection: ~5seconds */
	 STARTUP_SWIM_DELAY_5S;
	 /* ------------------------------------------- */
	
 

	/* configure all STM8L001 pins as input with pull up */
	//GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast); // pin 1 SWIM/AutoSHTDWN	
	GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast); // pin 2 RF PWRDWN
	GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast); // pin 5 unused
	GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast); // pin 6 unused
	GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_High_Fast); // pin 7 FSK Data
	GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast); // pin 8 ASK Data
	
		GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast); // pin 2 RF PWRDWN
	GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast); // pin 5 unused
	GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast); // pin 6 unused
	GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_High_Fast); // pin 7 FSK Data
	GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast); // pin 8 ASK Data
	//CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv1);	//Output clock on Pin 1
	//CLK_CCOConfig(CLK_Output_ClockMaster);
	/*
	TIM2_DeInit();
	TIM2_TimeBaseInit(TIM2_Prescaler_2, TIM2_CounterMode_Up, 	1);
	//TIM2_OC1Init(TIM2_OCMode_Active, TIM2_OutputState_Enable, 1000, TIM2_OCPolarity_Low, TIM2_OCIdleState_Reset);
	//TIM2_CtrlPWMOutputs(ENABLE);
	TIM2_Cmd(ENABLE);
*/
	while (1){
		//Set all GPIO to default behaviour
		//Reset_PWRDown();
		//Reset_ASKData();
		//Reset_FSKData();
		
		//Set_PWRDown();
		//PLL_On();
		GPIO_ToggleBits(GPIOB, GPIO_Pin_7);
                for(i=0;i<100;i++);
		
	}
	
}