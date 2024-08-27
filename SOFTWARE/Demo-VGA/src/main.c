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

void init_screen() {
    uint8_t ch = 0x20;
    for (uint8_t row = 0; row < NUM_ROWS; row++) {
        for (uint8_t col = 0; col < NUM_COLS; col++) {
            screen_chars[row][col] = ch++;
            if (ch > 0x7E) {
                ch = 0x20;
            }
        }
    }
}

extern void waste_time0();
extern void waste_time1();

#define WRITE_GLYPH_LINE(offset) \
    "c.lw   a3," #offset "(a2) \n"    /* load glyph scan line bits for column N */ \
    "c.sw   a3,0(a1) \n"    /* write to video-out pin */ \
    "c.srli a3,1 \n"        /* shift next bit into pin position */ \
    "c.sw   a3,0(a1) \n"    \
    "c.srli a3,1 \n"        \
    "c.sw   a3,0(a1) \n"    \
    "c.srli a3,1 \n"        \
    "c.sw   a3,0(a1) \n"    \
    "c.srli a3,1 \n"        \
    "c.sw   a3,0(a1) \n"    \
    "c.srli a3,1 \n"        \
    "c.sw   a3,0(a1) \n"    \
    "c.srli a3,1 \n"        \
    "c.sw   a3,0(a1) \n"    \
    "c.srli a3,1 \n"        \
    "c.sw   a3,0(a1) \n"

#define COPY_GLYPH_BITS(col) \
    glyph_lines[col] = char_defs[char_indexes[col]];


void write_scan_line(uint16_t row) {
    // Unroll the loop for columns
    __asm(\
    "la     a2,glyph_bits     \n" // load a2(x12) with glyph_bits array address
    "li     a1,0x40011010      \n" // load a1(x11) with BSHR address
    WRITE_GLYPH_LINE(0)
    WRITE_GLYPH_LINE(4)
    WRITE_GLYPH_LINE(8)
    WRITE_GLYPH_LINE(12)
    WRITE_GLYPH_LINE(16)
    WRITE_GLYPH_LINE(20)
    WRITE_GLYPH_LINE(24)
    WRITE_GLYPH_LINE(28)
    WRITE_GLYPH_LINE(32)
    WRITE_GLYPH_LINE(36)
    WRITE_GLYPH_LINE(40)
    WRITE_GLYPH_LINE(44)
    WRITE_GLYPH_LINE(48)
    WRITE_GLYPH_LINE(52)
    WRITE_GLYPH_LINE(56)
    WRITE_GLYPH_LINE(60)
    WRITE_GLYPH_LINE(64)
    WRITE_GLYPH_LINE(68)
    WRITE_GLYPH_LINE(72)
    WRITE_GLYPH_LINE(76)
    WRITE_GLYPH_LINE(80)
    );

    // Prepare the next text scan line (all columns)
    row += 1;
    register const uint32_t* char_defs = character_defs[row & 0x7]; // point to fixed array of scan line words
    register uint8_t* char_indexes = screen_chars[row >> 3]; // point to array of character codes (text line)
    register uint32_t* glyph_lines = glyph_bits; // point to array of glyph bits data for drawing

    COPY_GLYPH_BITS(0)
    COPY_GLYPH_BITS(1)
    COPY_GLYPH_BITS(2)
    COPY_GLYPH_BITS(3)
    COPY_GLYPH_BITS(4)
    COPY_GLYPH_BITS(5)
    COPY_GLYPH_BITS(6)
    COPY_GLYPH_BITS(7)
    COPY_GLYPH_BITS(8)
    COPY_GLYPH_BITS(9)
    COPY_GLYPH_BITS(10)
    COPY_GLYPH_BITS(11)
    COPY_GLYPH_BITS(12)
    COPY_GLYPH_BITS(13)
    COPY_GLYPH_BITS(14)
    COPY_GLYPH_BITS(15)
    COPY_GLYPH_BITS(16)
    COPY_GLYPH_BITS(17)
    COPY_GLYPH_BITS(18)
    COPY_GLYPH_BITS(19)
    COPY_GLYPH_BITS(20)
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
        /*
        for (uint8_t row = 0; row < NUM_ROWS; row++) {
            for (uint8_t col = 0; col < NUM_COLS; col++) {
                uint8_t* cursor = &screen_chars[row][col];
                uint8_t ch = *cursor + 1;
                if (ch > 0x7E) {
                    ch = 0x20;
                }
                *cursor = ch;
            }
        }*/
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

#define VADJUST 32

	uint32_t current_row = VGA_VSYNC_TIM->CNT;
	if (current_row < VGA_VBACK_PORCH+VADJUST || current_row >= VGA_VBACK_PORCH+VADJUST+(32*NUM_ROWS)) {
		goto exit;
	}

    waste_time0();
    write_scan_line((current_row-VGA_VBACK_PORCH-VADJUST) >> 2);

exit:
	VGA_DATA_GPIO->BCR = VGA_DATA_PIN;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
}
