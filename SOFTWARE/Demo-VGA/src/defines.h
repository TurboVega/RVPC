#ifndef DEFINES_H
#define DEFINES_H

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
    #define CLOCK_PRESCALER     2
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

	#define VGA_HSYNC_PERIOD  412
	#define VGA_HSYNC_PULSE    46
	#define VGA_HBACK_PORCH     8

    #define VGA_VACTIVE_LINES 480
	#define VGA_VPERIOD       525
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    12
	#define VGA_VFRONT_PORCH   10
#elif defined SYSCLK_FREQ_48MHZ_HSI
    #define CLOCK_PRESCALER     1
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

	#define VGA_HSYNC_PERIOD  824
	#define VGA_HSYNC_PULSE    92
	#define VGA_HBACK_PORCH    14
	
    #define VGA_VACTIVE_LINES 480
	#define VGA_VPERIOD       525
	#define VGA_VSYNC_PULSE     2

	#define VGA_VBACK_PORCH    12
	#define VGA_VFRONT_PORCH   10
#elif defined SYSCLK_FREQ_36MHZ_HSI
    #define CLOCK_PRESCALER     4 // 48MHz / 4 = 12MHz
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
#elif defined SYSCLK_FREQ_40MHZ_HSI
    #define CLOCK_PRESCALER     4 // 48MHz / 4 = 12MHz
    #define TICK_CNT_DIVIDER    3 // Converts 36MHz tick counts to 12MHz tick counts
    #define TIMER_OC_MODE       TIM_OCMode_PWM1

    #define VGA_HACTIVE_PIXELS 640
	#define VGA_HSYNC_PERIOD   ((833)/TICK_CNT_DIVIDER)
	#define VGA_HSYNC_PULSE     ((48)/TICK_CNT_DIVIDER)
	
    #define VGA_VACTIVE_LINES 480
	#define VGA_VPERIOD       509
	#define VGA_VSYNC_PULSE     3

	#define VGA_VBACK_PORCH    25
	#define VGA_VFRONT_PORCH    1
#endif

#endif // DEFINES_H
