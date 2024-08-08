#include <ch32v00x.h>
#define DEF_SCREEN_ARRAYS 1
#include "chardefs.h"

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
	#define VGA_HSYNC_PERIOD  412
	#define VGA_HSYNC_PULSE    46

	#define VGA_VPERIOD       525
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    12
	#define VGA_VFRONT_PORCH   10

	#define VGA_HBACK_PORCH     8

	#define CHECKER_COLUMNS    25
	#define CHECKER_ROWS       30
#elif defined SYSCLK_FREQ_48MHZ_HSI
	#define VGA_HSYNC_PERIOD  824
	#define VGA_HSYNC_PULSE    92
	
	#define VGA_VPERIOD       525
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    12
	#define VGA_VFRONT_PORCH   10

	#define VGA_HBACK_PORCH    14

	#define CHECKER_COLUMNS    44
	#define CHECKER_ROWS       20
#elif defined SYSCLK_FREQ_36MHZ_HSI
    #define CLOCK_PRESCALER     2 // 48MHz / 2 = 24MHz
    #define TICK_CNT_DIVIDER    3 // Converts 36MHz tick counts to 12MHz tick counts
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

    #define VGA_HACTIVE_PIXELS 800
	#define VGA_HSYNC_PERIOD  ((1024)/TICK_CNT_DIVIDER)
	#define VGA_HSYNC_PULSE     ((72)/TICK_CNT_DIVIDER)
	
    #define VGA_VACTIVE_LINES 600
	#define VGA_VPERIOD       625
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    22
	#define VGA_VFRONT_PORCH    1
#endif

// a0 x10   ((USE_BCR  << 0) | (USE_BCR  << 16))  pixels __ (0xC09CC09C)
// a1 x11   ((USE_BCR  << 0) | (USE_BSHR << 16))  pixels _* (0xC01CC09C)
// a2 x12   ((USE_BSHR << 0) | (USE_BCR  << 16))  pixels *_ (0xC09CC01C)
// a3 x13   ((USE_BSHR << 0) | (USE_BSHR << 16))  pixels ** (0xC01CC01C)
// a4 x14   address of dynamic code for 1 glyph scan line (8 pixels)

typedef void (*SetCodePiece)(uint32_t code0, uint32_t code1, uint32_t code2, uint32_t code3, uint32_t dyn_code);

void init_screen() {
    //uint8_t ch = 0;
    for (uint8_t row = 0; row < NUM_ROWS; row++) {
        for (uint8_t col = 0; col < NUM_COLS; col++) {
            screen_chars[row][col] = 'a';//ch++;
        }
    }
}

extern void set_dynamic_code();
extern void run_dynamic_code();
extern void write_pixels();
extern void waste_time0();
extern void waste_time1();

void prepare_scan_line(uint16_t row) {
    uint32_t col;
    register const uint8_t* char_defs = character_defs[row & 0x7]; // point to array of scan line bits
    register const uint8_t* char_indexes = screen_chars[row >> 3]; // point to array of character codes
    
    for (col = 0; col < 2/*NUM_COLS*/; col++) {
        uint8_t ch = *char_indexes++; // get one character code
        uint8_t def = char_defs[ch]; // get scan line bits for character
        uint32_t dyn_code = ((uint32_t) run_dynamic_code) + (col * 16); // 8 HW instructions per char column
        //SetCodePiece set_code = (SetCodePiece)(((uint32_t)set_dynamic_code) + (def * 10)); // 5 HW instructions per column
        //(*set_code)(0xC09CC09C, 0xC01CC09C, 0xC09CC01C, 0xC01CC01C, dyn_code);
        set_dynamic_code(0xC09CC09C, 0xC01CC09C, 0xC09CC01C, 0xC01CC01C, dyn_code);
    }
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
	PWM_Config(VGA_HSYNC_TIM, VGA_HSYNC_CH, VGA_HSYNC_PULSE, TIM_OCMode_PWM1);
	// Interrupt Config
	Timer_Interrupt(VGA_HSYNC_TIM);

	// VSync
	// Slave Timer Config
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM1, ENABLE);
	Slave_Timer_Config(VGA_VSYNC_TIM, VGA_HSYNC_TIM, TIM_TRGOSource_OC4Ref, VGA_VPERIOD, TIM_CounterMode_Up);
	// PWM Config
	PWM_Config(VGA_VSYNC_TIM, VGA_VSYNC_CH, VGA_VSYNC_PULSE, TIM_OCMode_PWM1);

	// Start timers
	TIM_Cmd(VGA_VSYNC_TIM, ENABLE);
	TIM_Cmd(VGA_HSYNC_TIM, ENABLE);

    init_screen();

	while (1) {
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

void TIM1_IRQHandler(void)   __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_IRQHandler(void) {
	// Vsync code here
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
}

void TIM2_IRQHandler(void)   __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) {
	static volatile uint32_t current_row = 0;

	current_row = VGA_VSYNC_TIM->CNT;
	if (current_row <= VGA_VBACK_PORCH || current_row >= (VGA_VPERIOD - VGA_VFRONT_PORCH)) {
		goto exit;
	}

    waste_time0();
    run_dynamic_code();

    current_row -= VGA_VBACK_PORCH;
    if (current_row < VGA_VACTIVE_LINES-1) {
        prepare_scan_line(current_row + 1);
    } else {
        prepare_scan_line(0);
    }

exit:
	GPIO_WriteBit(VGA_DATA_GPIO, VGA_DATA_PIN, 0);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
}
