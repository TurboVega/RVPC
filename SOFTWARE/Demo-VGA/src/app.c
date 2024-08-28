#include "chardefs.h"

void initialize_application() {

}

void run_keyboard_state_machine() {

}

void run_app_state_machine() {
    if (v_state == V_STATE_END_FRAME) {
        // Draw the next frame (array of character codes).
        v_state = V_STATE_FRAME_READY;
    }
}
