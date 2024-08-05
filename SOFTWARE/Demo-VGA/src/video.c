#include <ch32v00x.h>
#include "defines.h"
#define DEF_SCREEN_ARRAYS 1
#include "chardefs.h"

extern void init_screen();
extern void on_hblank_start(uint16_t current_row);
extern void on_hblank_continue(uint16_t current_row);
extern void on_vblank_start();
extern void on_vblank_continue();

void waste_time() {
    int i;
    for (i = 0; i < 170; i++) {
        VGA_DATA_GPIO->BCR = VGA_DATA_PIN;
    }
}

void prepare_scan_line(uint16_t row) {
    //register const uint8_t* char_defs = character_defs[row & 0x7];
    //register const uint8_t* char_indexes = screen_chars[row >> 3];
}

extern void run_dynamic_code();

void run_video_loop() {
    // Init screen with test data
    init_screen();

    uint16_t prior_row = VGA_VSYNC_TIM->CNT;
	while (1) {
        register uint16_t current_row = VGA_VSYNC_TIM->CNT;
        if (current_row != prior_row) {
            prior_row = current_row;
            current_row >>= 1;
            uint16_t lo = 36;
            uint16_t hi = (VGA_VACTIVE_LINES >> 1);
            if (current_row >= lo && current_row < hi) {
                waste_time();

                run_dynamic_code();
                VGA_DATA_GPIO->BCR = VGA_DATA_PIN;

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