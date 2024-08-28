// File: app.c
// Purpose: Sample text-based application
//

#include "chardefs.h"

void initialize_application() {
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

void run_keyboard_state_machine() {

}

void run_app_state_machine() {
    if (v_state == V_STATE_END_FRAME) {
        // Draw the next frame (array of character codes).
        v_state = V_STATE_FRAME_READY;
    }
}
