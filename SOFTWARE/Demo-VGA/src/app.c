// File: app.c
// Purpose: Sample text-based application
//

#include "chardefs.h"

void initialize_application() {
    for (uint8_t row = 0; row < NUM_ROWS; row++) {
        screen_chars[row][0] = row / 10 + '0';
        screen_chars[row][1] = row % 10 + '0';
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
