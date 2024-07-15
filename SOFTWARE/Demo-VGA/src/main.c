#include <ch32v00x.h>

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

void Timer_Interrupt(TIM_TypeDef *TIM) {
	NVIC_InitTypeDef NVIC_InitStruct;

	if (TIM == TIM1) {
		TIM_ITConfig(TIM, TIM_IT_Update, ENABLE);
		NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
	} else if (TIM == TIM2) {
		TIM_ITConfig(TIM, TIM_IT_Update, ENABLE);
		NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	}

	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
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

#define VGA_DATA_GPIO   GPIOC
#define VGA_DATA_PIN    GPIO_Pin_2

#define VGA_HSYNC_GPIO  GPIOC
#define VGA_HSYNC_PIN   GPIO_Pin_1
#define VGA_HSYNC_TIM   TIM2
#define VGA_HSYNC_CH    4

#define VGA_VSYNC_GPIO  GPIOA
#define VGA_VSYNC_PIN   GPIO_Pin_1
#define VGA_VSYNC_TIM   TIM1
#define VGA_VSYNC_CH    2

#ifdef SYSCLK_FREQ_24MHZ_HSI
    #define CLOCK_PRESCALER     4
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

	#define VGA_HSYNC_PERIOD  412
	#define VGA_HSYNC_PULSE    46
	#define VGA_HBACK_PORCH     8

	#define VGA_VPERIOD       525
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    12
	#define VGA_VFRONT_PORCH   10

	#define CHECKER_COLUMNS    25
	#define CHECKER_ROWS       30
#elif defined SYSCLK_FREQ_48MHZ_HSI
    #define CLOCK_PRESCALER     2
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

	#define VGA_HSYNC_PERIOD  824
	#define VGA_HSYNC_PULSE    92
	#define VGA_HBACK_PORCH    14
	
	#define VGA_VPERIOD       525
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    12
	#define VGA_VFRONT_PORCH   10

	#define CHECKER_COLUMNS    44
	#define CHECKER_ROWS       20
#elif defined SYSCLK_FREQ_6MHZ_HSI
    #define CLOCK_PRESCALER     4 // 48MHz / 4 = 12MHz
    #define TICK_CNT_DIVIDER    6 // Converts 36MHz tick counts to 6MHz tick counts
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

    #define VGA_HACTIVE_PIXELS 800
	#define VGA_HBACK_PORCH    ((128)/TICK_CNT_DIVIDER) // 22
	#define VGA_HSYNC_PERIOD  ((1024)/TICK_CNT_DIVIDER) // 171
	#define VGA_HSYNC_PULSE     ((72)/TICK_CNT_DIVIDER) // 12
	
    #define VGA_VACTIVE_LINES 600
	#define VGA_VPERIOD       625
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    22
	#define VGA_VFRONT_PORCH    1

	#define CHECKER_COLUMNS    10
	#define CHECKER_ROWS       10
#endif

void waste_time() {
    volatile uint32_t* clr = &VGA_DATA_GPIO->BCR;

    // 0
    *clr = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 9
    *clr = VGA_DATA_PIN;

    // 20
    *clr = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 9
    *clr = VGA_DATA_PIN;

    // 40
    *clr = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *clr = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;

}

void write_pixels() {
    volatile uint32_t* clr = &VGA_DATA_GPIO->BCR;
    volatile uint32_t* set = &VGA_DATA_GPIO->BSHR;

    // 0
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;
/*
    // 20
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 40
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 60
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 80
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 100
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 120
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 140
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;

    // 160
    *set = VGA_DATA_PIN; // 0
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 1
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 2
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 3
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 4
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 5
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 6
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 7
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 8
    *clr = VGA_DATA_PIN;
    *set = VGA_DATA_PIN; // 9
    *set = VGA_DATA_PIN;
*/
}

int main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	SystemCoreClockUpdate();
	
	// Disable GPIO Alternate Functions and extrnal oscilator
	// Othewize GPIO PORT A does not work
	RCC_HSEConfig(RCC_HSE_OFF);
	GPIO_PinRemapConfig(GPIO_Remap_PA1_2, DISABLE);

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
	// Interrupt Config
	//Timer_Interrupt(VGA_HSYNC_TIM);

	// VSync
	// Slave Timer Config
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM1, ENABLE);
	Slave_Timer_Config(VGA_VSYNC_TIM, VGA_HSYNC_TIM, TIM_TRGOSource_OC4Ref, VGA_VPERIOD, TIM_CounterMode_Up);
	// PWM Config
	PWM_Config(VGA_VSYNC_TIM, VGA_VSYNC_CH, VGA_VSYNC_PULSE, TIMER_OC_MODE);

	// Start timers
	TIM_Cmd(VGA_VSYNC_TIM, ENABLE);
	TIM_Cmd(VGA_HSYNC_TIM, ENABLE);

    uint16_t prior_row = VGA_VSYNC_TIM->CNT;
	while (1) {
        volatile uint16_t current_row = VGA_VSYNC_TIM->CNT;
        if (current_row != prior_row) {
            prior_row = current_row;
            /*if ((current_row >= VGA_VBACK_PORCH) &&
                (current_row < VGA_VBACK_PORCH + VGA_VACTIVE_LINES)) {
                for (int i = 0; i < 2; i++) waste++;
                write_pixels();
            }*/
            if ((current_row >= 300) &&
                (current_row < 320)) {
                waste_time();
                write_pixels();
            }
            volatile uint32_t* clr = &VGA_DATA_GPIO->BCR;
            *clr = VGA_DATA_PIN;
        }
	}
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

//void TIM1_IRQHandler(void)   __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM1_IRQHandler(void) {
//	// Vsync code here
//	TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
//}

//void TIM2_IRQHandler(void)   __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM2_IRQHandler(void) {
//	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
//}
