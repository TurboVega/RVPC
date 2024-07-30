#include <ch32v00x.h>
#include "defines.h"

void GPIO_Config(GPIO_TypeDef *GPIO_port, uint16_t GPIO_pin, GPIOMode_TypeDef GPIO_mode) {
	GPIO_InitTypeDef Config = {0};

	if (GPIO_port == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (GPIO_port == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	} else if (GPIO_port == GPIOD) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}

	Config.GPIO_Pin = GPIO_pin;
	Config.GPIO_Mode = GPIO_mode;
	Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_port, &Config);
}

void Timer_Config(TIM_TypeDef *TIM, uint16_t period, uint16_t prescaler, uint16_t mode) {
	TIM_TimeBaseInitTypeDef TimerConfig;

	if (TIM == TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	} else if (TIM == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}

 	TimerConfig.TIM_Period = period;
	TimerConfig.TIM_Prescaler = prescaler;
	TimerConfig.TIM_CounterMode = mode;
	TimerConfig.TIM_ClockDivision = TIM_CKD_DIV1;	
	TIM_TimeBaseInit(TIM, &TimerConfig);
}

void Slave_Timer_Config(TIM_TypeDef *TIM_Slave, TIM_TypeDef *TIM_Master, uint16_t TIM_TRGOSource, uint16_t period, uint16_t mode) {
	if (TIM_Slave == TIM_Master) {
		return;
	}

	TIM_SelectOutputTrigger(TIM_Master, TIM_TRGOSource);

	if (TIM_Slave == TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	} else if (TIM_Slave == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}

	TIM_CounterModeConfig(TIM_Slave, mode);
	TIM_ITRxExternalClockConfig(TIM_Slave, TIM_TS_ITR1);
	TIM_SelectSlaveMode(TIM_Slave, TIM_SlaveMode_External1);
	TIM_SetAutoreload(TIM_Slave, period);
}

void PWM_Config(TIM_TypeDef *TIM, uint8_t channel, uint16_t pulse, uint16_t mode) {
	TIM_OCInitTypeDef TIM_OCConfig={0};
	TIM_OCConfig.TIM_Pulse = pulse;
	TIM_OCConfig.TIM_OCMode = mode;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;

	switch (channel) {
		case 1:
			TIM_OC1Init(TIM, &TIM_OCConfig );
		break;
		case 2:
			TIM_OC2Init(TIM, &TIM_OCConfig );
		break;
		case 3:
			TIM_OC3Init(TIM, &TIM_OCConfig );
		break;
		case 4:
			TIM_OC4Init(TIM, &TIM_OCConfig );
		break;
	}

	TIM_CtrlPWMOutputs(TIM, ENABLE );

	switch (channel) {
		case 1:
			TIM_OC1PreloadConfig(TIM, TIM_OCPreload_Disable);
		break;
		case 2:
			TIM_OC2PreloadConfig(TIM, TIM_OCPreload_Disable);
		break;
		case 3:
			TIM_OC3PreloadConfig(TIM, TIM_OCPreload_Disable);
		break;
		case 4:
			TIM_OC4PreloadConfig(TIM, TIM_OCPreload_Disable);
		break;
	}

	TIM_ARRPreloadConfig(TIM, ENABLE);
}

void configure_peripherals() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	SystemCoreClockUpdate();
	
	// Disable GPIO Alternate Functions and extrnal oscilator
	// Othewize GPIO PORT A does not work
	RCC_HSEConfig(RCC_HSE_OFF);
	GPIO_PinRemapConfig(GPIO_Remap_PA1_2, DISABLE);

    // HSI clock trim
    //RCC->CTLR = (RCC->CTLR & ~0xF8) | (4<<3);

	// Remapping
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// VGA GPIOs Config
	GPIO_Config(VGA_DATA_GPIO,  VGA_DATA_PIN,  GPIO_Mode_Out_PP);
	GPIO_Config(VGA_HSYNC_GPIO, VGA_HSYNC_PIN, GPIO_Mode_AF_PP);
	GPIO_Config(VGA_VSYNC_GPIO, VGA_VSYNC_PIN, GPIO_Mode_AF_PP);

	// HSync
	// Timer Config
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	Timer_Config(VGA_HSYNC_TIM, VGA_HSYNC_PERIOD, (CLOCK_PRESCALER-1), TIM_CounterMode_Up);
	// PWM Config
	PWM_Config(VGA_HSYNC_TIM, VGA_HSYNC_CH, VGA_HSYNC_PULSE, TIMER_OC_MODE);

	// VSync
	// Slave Timer Config
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM1, ENABLE);
	Slave_Timer_Config(VGA_VSYNC_TIM, VGA_HSYNC_TIM, TIM_TRGOSource_OC4Ref, VGA_VPERIOD, TIM_CounterMode_Up);
	// PWM Config
	PWM_Config(VGA_VSYNC_TIM, VGA_VSYNC_CH, VGA_VSYNC_PULSE, TIMER_OC_MODE);

	// Start timers
	TIM_Cmd(VGA_VSYNC_TIM, ENABLE);
	TIM_Cmd(VGA_HSYNC_TIM, ENABLE);
}

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_Handler(void) {
	SysTick->SR = 0;
}

void NMI_Handler(void)       __attribute__((interrupt("WCH-Interrupt-fast")));
void NMI_Handler(void) {
	
}

void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast"))); 
void HardFault_Handler(void) {
	while (1) {
		
	}
}
