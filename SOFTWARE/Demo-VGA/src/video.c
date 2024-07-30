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
    return p + 10; // skip first 5 WORD instructions
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

void run_video_loop() {
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
}