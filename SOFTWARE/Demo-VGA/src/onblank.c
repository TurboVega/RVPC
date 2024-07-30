#include "chardefs.h"

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
