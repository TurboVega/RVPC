// File: app.c
// Purpose: Sample text-based application
//
// This app implements a solution to the Towers-of-Hanoi problem.
//

#include "chardefs.h"
#include <string.h>

// How portions the screen might look:
//
//    000000000011111111112
//    012345678901234567890
//   +---------------------+
// 00| ==== RVPC Demo ==== |
// 01|                     |
// 02|      /---\          |
// 03|      \_3_/          |
// 04|    P       P     P  |
// 05|    P       P     P  |
// 06|   /-\      P     P  |
// 07|   \1/      P     P  |
// 08|  /---\    /-\    P  |
// 09|  \_3_/    \1/    P  |
// 10| /-----\  /---\  /-\ |
// 11| \__5__/  \_3_/  \1/ |
// 12|/-------\/-----\/---\|
// 13|\___7___/\__5__/\_3_/|
// 14|   [=]     [=]   [=] |
// 15|    A       B     C  |
// 16|                     |
// 17| Move #5 from A to B |
//   +---------------------+
//

#define TITLE_ROW       0
#define BASE_ROW       14
#define LETTER_ROW     15
#define STATUS_ROW     17

#define NUM_PEGS        3
#define PEG_HEIGHT     10
#define MAX_RINGS       4
#define RING_HEIGHT     2
#define MIN_RING_WIDTH  

void write_at(uint8_t row, uint8_t col, char ch) {
    screen_chars[row][col] = ch;
}

void print_at(uint8_t row, uint8_t col, const char* text) {
    char* ch;
    while (ch = *text++) {
        screen_chars[row][col++] = ch;
    }
}

void initialize_application() {
    // Fill the screen with blank characters
    memset(screen_chars, 0x20, sizeof(screen_chars));

    // Write constant texts
    print_at(TITLE_ROW, 1, "==== RVPC Demo ====");
    print_at(STATUS_ROW, 1, "Move #  from   to");
}

void run_keyboard_state_machine() {

}

void run_app_state_machine() {
    if (v_state == V_STATE_END_FRAME) {
        // Draw the next frame (array of character codes).
        v_state = V_STATE_FRAME_READY;
    }
}
