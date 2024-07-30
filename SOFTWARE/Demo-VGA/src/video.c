#include <ch32v00x.h>
#include "defines.h"
#define DEF_SCREEN_ARRAYS 1
#include "chardefs.h"

void init_screen();
void on_hblank_start(uint16_t current_row);
void on_hblank_continue(uint16_t current_row);
void on_vblank_start();
void on_vblank_continue();

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

#define ASM_CLR_VIDEO   __asm(" c.sw x10,0(x9)"); /* clear video-out bit */
#define ASM_SET_VIDEO   __asm(" c.sw x10,0(x8)"); /* set video-out bit */

#define WRITE_VIDEO_8 \
    ASM_CLR_VIDEO \
    ASM_SET_VIDEO \
    ASM_CLR_VIDEO \
    ASM_SET_VIDEO \
    ASM_CLR_VIDEO \
    ASM_SET_VIDEO \
    ASM_CLR_VIDEO \
    ASM_SET_VIDEO

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
    //DYN_CODE(0x10, 2, 3)
    //DYN_CODE(0x20, 4, 5)
    //DYN_CODE(0x30, 6, 7)
    //DYN_CODE(0x40, 8, 9)
    //DYN_CODE(0x50, 10, 11)
    //DYN_CODE(0x60, 12, 13)
    //DYN_CODE(0x70, 14, 15)
    //DYN_CODE(0x80, 16, 17)
    //DYN_CODE(0x90, 18, 19)
    //DYN_CODE(0xA0, 20, 21)
    //DYN_CODE(0xB0, 22, 23)
    //DYN_CODE(0xC0, 24, 25)
    //DYN_CODE(0xD0, 26, 27)
    //DYN_CODE(0xE0, 28, 29)
}

uint16_t* __attribute__((section(".data"))) write_pixels() {
write_pix:
    WRITE_VIDEO_8 // 0
    WRITE_VIDEO_8 // 1
    WRITE_VIDEO_8 // 2
    WRITE_VIDEO_8 // 3
    WRITE_VIDEO_8 // 4
    WRITE_VIDEO_8 // 5
    WRITE_VIDEO_8 // 6
    WRITE_VIDEO_8 // 7
    WRITE_VIDEO_8 // 8
    WRITE_VIDEO_8 // 9
    WRITE_VIDEO_8 // 10
    WRITE_VIDEO_8 // 11
    WRITE_VIDEO_8 // 12
    WRITE_VIDEO_8 // 13
    WRITE_VIDEO_8 // 14
    WRITE_VIDEO_8 // 15
    WRITE_VIDEO_8 // 16
    WRITE_VIDEO_8 // 17
    WRITE_VIDEO_8 // 18
    WRITE_VIDEO_8 // 19
    WRITE_VIDEO_8 // 20
    WRITE_VIDEO_8 // 21
    WRITE_VIDEO_8 // 22
    WRITE_VIDEO_8 // 23
    WRITE_VIDEO_8 // 24
    WRITE_VIDEO_8 // 25
    WRITE_VIDEO_8 // 26
    WRITE_VIDEO_8 // 27
    WRITE_VIDEO_8 // 28
/*
    WRITE_VIDEO_8 // 29
*/
    uint16_t* ptr_to_code = &&write_pix;
    return ptr_to_code;
}

void run_video_loop() {
    // Init screen with test data
    init_screen();
    
    __asm(
    "       la      x11,run_dynamic_code\n" // load x11 with address of dynamic code
    "       lui     x8,0x40011\n"           // load upper 20 bits of x8 with BSHR address
    "       addi    x8,x8,0x010\n"          // load lower 12 bits of x8 with BSHR address
    "       lui     x9,0x40011\n"           // load upper 20 bits of x9 with BCR address
    "       addi    x9,x9,0x014\n"          // load lower 12 bits of x9 with BCR address
    "       lui     x12,0x40012\n"          // load upper 20 bits of x12 with TIM1->CNT address
    "       addi    x12,x12,0xC24\n"        // load lower 12 bits of x12 with TIM1->CNT address
    "       addi    x10,x0,4\n"             // load x10 with bit value of video-out
    "       mov     x22,x0\n"               // clear prior row index
    "       mov     x23,x0\n"               // clear current row index
    );

/*
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

                uint16_t next_row = (prior_row + 1) >> 1;
                if ((next_row != prior_row) && (next_row < (VGA_VACTIVE_LINES >> 1))) {
                    prepare_scan_line(next_row);
                }

                on_hblank_start(current_row);
            } else if (current_row == (VGA_VACTIVE_LINES >> 1)) {
                on_vblank_start();
            } else if (current_row >= (VGA_VPERIOD >> 1)) {
                prepare_scan_line(0);
            } else {
                on_vblank_continue();
            }
        } else {
            on_hblank_continue(current_row);
        }
	}
*/
}