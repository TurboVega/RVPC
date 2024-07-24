#include <ch32v00x.h>
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
    #define CLOCK_PRESCALER     2 // 48MHz / 2 = 24MHz
    #define TICK_CNT_DIVIDER    3 // Converts 36MHz tick counts to 6MHz tick counts
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

    #define VGA_HACTIVE_PIXELS 800
	//#define VGA_HBACK_PORCH    ((128)/TICK_CNT_DIVIDER)
	#define VGA_HSYNC_PERIOD  ((1024)/TICK_CNT_DIVIDER)
	#define VGA_HSYNC_PULSE     ((72)/TICK_CNT_DIVIDER)
	
    #define VGA_VACTIVE_LINES 600
	#define VGA_VPERIOD       625
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    22
	#define VGA_VFRONT_PORCH    1

	#define CHECKER_COLUMNS    10
	#define CHECKER_ROWS       10
#endif

#define WASTE_5 \
    *clr = VGA_DATA_PIN; \
    *clr = VGA_DATA_PIN; \
    *clr = VGA_DATA_PIN; \
    *clr = VGA_DATA_PIN; \
    *clr = VGA_DATA_PIN;

#define WASTE_TIME \
    switch (current_row & 0x03) { \
        case 0: { \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            break; \
        } \
        case 1: { \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            break; \
        } \
        case 2: { \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            WASTE_5; \
            break; \
        } \
        case 3: { \
            WASTE_5; \
            WASTE_5; \
            break; \
        } \
    }

#define USE_BSHR    0xC008
#define USE_BCR     0xC088

#define DYN_CODE(index,col1,col2) \
    chardef = char_defs[char_indexes[col1]]; \
    instructions[index+0x00] = (chardef & 0x80) ? USE_BSHR : USE_BCR; \
    instructions[index+0x01] = (chardef & 0x40) ? USE_BSHR : USE_BCR; \
    instructions[index+0x02] = (chardef & 0x20) ? USE_BSHR : USE_BCR; \
    instructions[index+0x03] = (chardef & 0x10) ? USE_BSHR : USE_BCR; \
    instructions[index+0x04] = (chardef & 0x08) ? USE_BSHR : USE_BCR; \
    instructions[index+0x05] = (chardef & 0x04) ? USE_BSHR : USE_BCR; \
    instructions[index+0x06] = (chardef & 0x02) ? USE_BSHR : USE_BCR; \
    instructions[index+0x07] = (chardef & 0x01) ? USE_BSHR : USE_BCR; \
    \
    chardef = char_defs[char_indexes[col2]]; \
    instructions[index+0x08] = (chardef & 0x80) ? USE_BSHR : USE_BCR; \
    instructions[index+0x09] = (chardef & 0x40) ? USE_BSHR : USE_BCR; \
    instructions[index+0x0A] = (chardef & 0x20) ? USE_BSHR : USE_BCR; \
    instructions[index+0x0B] = (chardef & 0x10) ? USE_BSHR : USE_BCR; \
    instructions[index+0x0C] = (chardef & 0x08) ? USE_BSHR : USE_BCR; \
    instructions[index+0x0D] = (chardef & 0x04) ? USE_BSHR : USE_BCR; \
    instructions[index+0x0E] = (chardef & 0x02) ? USE_BSHR : USE_BCR; \
    instructions[index+0x0F] = (chardef & 0x01) ? USE_BSHR : USE_BCR;

uint16_t* write_pix_instructions;

void prepare_scan_line(uint16_t row) {
    register const uint8_t* char_defs = character_defs[row & 0x7];
    register const uint8_t* char_indexes = screen_chars[row >> 3];
    register uint16_t* instructions = write_pix_instructions;

    register uint8_t chardef;
    DYN_CODE(0x00, 0, 1)
    DYN_CODE(0x10, 2, 3)
    DYN_CODE(0x20, 4, 5)
    DYN_CODE(0x30, 6, 7)
    DYN_CODE(0x40, 8, 9)
    DYN_CODE(0x50, 10, 11)
    DYN_CODE(0x60, 12, 13)
    DYN_CODE(0x70, 14, 15)
    DYN_CODE(0x80, 16, 17)
    DYN_CODE(0x90, 18, 19)
    DYN_CODE(0xA0, 20, 21)
    DYN_CODE(0xB0, 22, 23)
    DYN_CODE(0xC0, 24, 25)
    DYN_CODE(0xD0, 26, 27)
    //DYN_CODE(0xE0, 28, 29)
}

void init_screen() {
    //uint8_t ch = 0;
    for (uint8_t row = 0; row < NUM_ROWS; row++) {
        for (uint8_t col = 0; col < NUM_COLS; col++) {
            screen_chars[row][col] = 'a';//ch++;
        }
    }
}

void on_hblank_start(uint16_t current_row) {
}

void on_hblank_continue(uint16_t current_row) {
}

void on_vblank_start() {
}

void on_vblank_continue() {
}

uint16_t* __attribute__((section(".data"))) run_dynamic_code() {
    __asm(" lui x8,0x40011");   // load upper 20 bits of x8 with BSHR address
    __asm(" addi x8,x8,0x010"); // load lower 12 bits of x8 with BSHR address
    __asm(" lui x9,0x40011");   // load upper 20 bits of x9 with BCR address
    __asm(" addi x9,x9,0x014"); // load lower 12 bits of x9 with BCR address
    __asm(" addi x10,x0,4");    // load x10 with bit value of video-out

write_pix:

    // 0
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit

    // 1
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 2
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 3
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 4
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 5
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 6
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 7
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 8
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 9
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 10
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 11
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 12
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 13
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 14
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 15
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 16
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 17
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 18
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 19
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 20
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 21
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 22
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 23
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 24
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 25
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 26
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 27
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit

    // 28
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
/*
    // 29
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
    __asm(" c.sw x10,0(x8)");   // set video-out bit
    __asm(" c.sw x10,0(x9)");   // clear video-out bit
*/
    uint16_t* p = &&write_pix;
    return p + 10;
}

void init_dynamic_code() {
    write_pix_instructions = run_dynamic_code();
    uint16_t* write_pix = write_pix_instructions;
    for (int col = 0; col < 29; col++) {
        write_pix[col*8+0] = USE_BSHR;
        write_pix[col*8+1] = USE_BCR;
        write_pix[col*8+2] = USE_BSHR;
        write_pix[col*8+3] = USE_BCR;
        write_pix[col*8+4] = USE_BCR;
        write_pix[col*8+5] = USE_BSHR;
        write_pix[col*8+6] = USE_BSHR;
        write_pix[col*8+7] = USE_BCR;
    }

    /*
    for (int col = 29; col < NUM_COLS; col++) {
        for (int bit = 0; bit < 8; bit+=2) {
            write_pix[col*8+bit] = USE_BCR;
            write_pix[col*8+bit+1] = USE_BCR;
        }
    }
    */

    //prepare_scan_line(6);
}

int main(void) {
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

    // Init screen with test data
    init_screen();
    
    // Initialize the more static parts of the dynamic code
    init_dynamic_code();

    // Draw the screen (character glyphs) repeatedly
    register volatile uint32_t* clr = &VGA_DATA_GPIO->BCR;

    uint16_t prior_row = VGA_VSYNC_TIM->CNT;
	while (1) {
        register uint16_t current_row = VGA_VSYNC_TIM->CNT;
        if (current_row != prior_row) {
            prior_row = current_row;
            current_row >>= 1;
            uint16_t lo = 36;
            uint16_t hi = (VGA_VACTIVE_LINES >> 1);
            if (current_row >= lo && current_row < hi) {
                //WASTE_TIME;
                //WASTE_TIME;

                WASTE_5;
                WASTE_5;
                WASTE_5;
                WASTE_5;
                WASTE_5;
                WASTE_5;
                WASTE_5;
                WASTE_5;
                WASTE_5;
                *clr = VGA_DATA_PIN;
                *clr = VGA_DATA_PIN;
                *clr = VGA_DATA_PIN;
                *clr = VGA_DATA_PIN;

                *clr = VGA_DATA_PIN;
                *clr = VGA_DATA_PIN;
                *clr = VGA_DATA_PIN;
                *clr = VGA_DATA_PIN;

                run_dynamic_code();
                *clr = VGA_DATA_PIN;

                /*uint16_t next_row = (prior_row + 1) >> 1;
                if ((next_row != prior_row) && (next_row < (VGA_VACTIVE_LINES >> 1))) {
                    prepare_scan_line(next_row);
                }*/

                on_hblank_start(current_row);
            } else if (current_row == (VGA_VACTIVE_LINES >> 1)) {
                on_vblank_start();
            } else if (current_row >= (VGA_VPERIOD >> 1)) {
                //prepare_scan_line(0);
            } else {
                on_vblank_continue();
            }
        } else {
            on_hblank_continue(current_row);
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
