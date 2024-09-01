// File: app.c
// Purpose: Sample text-based application
//
// This app implements a solution to the Towers-of-Hanoi problem.
//

#include "chardefs.h"
#include <string.h>
#include <stdbool.h>

// How portions the screen might look:
//
//    000000000011111111112
//    012345678901234567890
//   +---------------------+
// 00|===== RVPC Demo =====|
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
#define PEG_TOP_ROW     4
#define FIRST_RING_ROW  2
#define LAST_RING_ROW  13
#define PEG_BASE_ROW   14
#define LETTER_ROW     15
#define STATUS_ROW     17

#define RING_COL        7
#define FROM_COL       14
#define TO_COL         19

#define NUM_PEGS        3
#define NUM_RINGS       4
#define RING_HEIGHT     2
#define PEG_BASE_WIDTH  3

// Character codes:
#define CC_TOP_OF_PEG           0x00
#define CC_SHAFT_OF_PEG         0x01
#define CC_CENTER_OF_PEG_BASE   0x02
#define CC_LEFT_OF_PEG_BASE     0x03
#define CC_RIGHT_OF_PEG_BASE    0x04
#define CC_UP_LEFT_OF_RING      0x05
#define CC_UP_CENTER_OF_RING    0x06
#define CC_UP_RIGHT_OF_RING     0x07
#define CC_LW_LEFT_OF_RING      0x08
#define CC_LW_CENTER_OF_RING    0x09
#define CC_LW_RIGHT_OF_RING     0x0A

#define DIR_NONE        0
#define DIR_UP          1
#define DIR_RIGHT       2
#define DIR_DOWN        3
#define DIR_LEFT        4

// Frame rate is 56 Hz, with pixel clock at 36 MHz
#define SCREEN_FPS      56
#define STARTUP_DELAY   (SCREEN_FPS*10)  // 10 seconds
#define SOLUTION_DELAY  (SCREEN_FPS*5)   // 5 seconds
#define MOVE_DELAY      (SCREEN_FPS/7)   // 1/7 second

typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t extend;
    uint8_t start;
    uint8_t end;
    uint8_t width;
    uint8_t peg;
} Ring;

typedef struct {
    uint8_t name;
    uint8_t col;
    uint8_t count;
    uint8_t rings[NUM_RINGS];
} Peg;

typedef struct {
    uint8_t count;
    uint8_t ring;
    uint8_t from;
    uint8_t to;
    uint8_t spare;
} Move;

Ring rings[NUM_RINGS] = {
    { LAST_RING_ROW-RING_HEIGHT*3, 4, 1, 3, 5, 3, 0 },
    { LAST_RING_ROW-RING_HEIGHT*2, 4, 2, 2, 6, 5, 0 },
    { LAST_RING_ROW-RING_HEIGHT*1, 4, 3, 1, 7, 7, 0 },
    { LAST_RING_ROW-RING_HEIGHT*0, 4, 4, 0, 8, 9, 0 }
};

Peg pegs[NUM_PEGS] = {
    { 'A', 4, NUM_RINGS, { 3, 2, 1, 0 }},
    { 'B', 13, 0, { 0, 0, 0, 0 }},
    { 'C', 19, 0, { 0, 0, 0, 0 }}
};

uint8_t direction = DIR_NONE;
uint16_t delay = STARTUP_DELAY;
Ring* active_ring = NULL;
Move stack[12];
uint8_t moves;
uint8_t dest_row;
uint8_t dest_col;

void write_at(uint8_t row, uint8_t col, char ch) {
    screen_chars[row][col] = ch;
}

void print_at(uint8_t row, uint8_t col, const char* text) {
    char ch;
    while ((ch = *text++)) {
        screen_chars[row][col++] = ch;
    }
}

void draw_peg(const Peg* peg) {
    uint8_t row = PEG_TOP_ROW;
    write_at(row++, peg->col, CC_TOP_OF_PEG);
    while (row < PEG_BASE_ROW) {
        write_at(row++, peg->col, CC_SHAFT_OF_PEG);
    }
    write_at(row, peg->col-1, CC_LEFT_OF_PEG_BASE);
    write_at(row, peg->col, CC_CENTER_OF_PEG_BASE);
    write_at(row, peg->col+1, CC_RIGHT_OF_PEG_BASE);
    write_at(row+1, peg->col, peg->name);
}

void draw_ring(const Ring* ring) {
    write_at(ring->row-1, ring->start, CC_UP_LEFT_OF_RING);
    write_at(ring->row, ring->start, CC_LW_LEFT_OF_RING);
    uint8_t col = ring->start;
    while (++col < ring->end) {
        write_at(ring->row-1, col, CC_UP_CENTER_OF_RING);
        write_at(ring->row, col, CC_LW_CENTER_OF_RING);
    }
    write_at(ring->row-1, col, CC_UP_RIGHT_OF_RING);
    write_at(ring->row, col, CC_LW_RIGHT_OF_RING);
}

void animate_frame() {
    // Fill middle section of screen with blank characters
    memset((void*)screen_chars[1], 0x20, NUM_COLS*(NUM_ROWS-3));

    // Draw pieces
    draw_peg(&pegs[0]);
    draw_peg(&pegs[1]);
    draw_peg(&pegs[2]);
    draw_ring(&rings[0]); // 1+7+1 wide
    draw_ring(&rings[1]); // 1+5+1 wide
    draw_ring(&rings[2]); // 1+3+1 wide
    draw_ring(&rings[3]); // 1+1+1 wide
}

uint8_t get_peg_footprint(const Peg* peg, uint8_t width) {
    if (peg->count) {
        Ring* ring = &rings[peg->rings[0]];
        if (ring->width > width) {
            width = ring->width;
        }
    }
    return width;
}

void adjust_peg_columns() {
    // Because of limited screen columns, bottom-most
    // ring widths and currently moving ring width determine
    // required widths of pegs, and positions of all pegs.
    uint8_t width0 = get_peg_footprint(&pegs[0], (move->to == 0 ? ring->width : PEG_BASE_WIDTH));
    uint8_t width1 = get_peg_footprint(&pegs[1], (move->to == 1 ? ring->width : PEG_BASE_WIDTH));
    uint8_t width2 = get_peg_footprint(&pegs[2], (move->to == 2 ? ring->width : PEG_BASE_WIDTH));

    pegs[0].col = width0 / 2;
    pegs[1].col = width0 + width1 / 2;
    pegs[2].col = width0 + width1 + width2 / 2;

    // Relocate any rings that move with a peg
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
        uint8_t old_col = rings[r].col;
        uint8_t new_col = pegs[rings[r].peg].col;
        rings[r].col = new_col;
        rings[r].start += new_col - old_col;
        rings[r].end += new_col - old_col;
    }

    // Determine where the moving ring will stop
    peg = &pegs[move->to];
    dest_row = LAST_RING_ROW - peg->count * RING_HEIGHT;
    dest_col = peg->col;
}

void start_move() {
    // Determine which ring to move.
    Move* move = &stack[moves - 1];
    Peg* peg = &pegs[move->from];
    uint8_t ring_index = peg->rings[peg->count - 1];
    move->ring = ring_index;
    Ring* ring = &rings[ring_index];

    // Update the status info on screen
    write_at(STATUS_ROW, RING_COL, move->ring + '1');
    write_at(STATUS_ROW, FROM_COL, move->from + 'A');
    write_at(STATUS_ROW, TO_COL, move->to + 'A');

    // Start the move.
    delay = MOVE_DELAY;
    direction = DIR_UP;
    active_ring = ring;
}

void push_move(uint8_t count, uint8_t from, uint8_t spare, uint8_t to) {
    // Push a move onto the stack.
    Move* move = &stack[moves++];
    move->count = count;
    move->from = from;
    move->to = to;
    move->spare = spare;

    if (count > 1) {
        // Move all but the bottom ring, so that
        // we can get to the bottom ring.
        push_move(count - 1, from, to, spare);
    } else {
        start_move();
    }
}

void pop_move() {
    Move* move = &stack[moves - 1]; // points to move just completed
    moves--;
    if (move->count > 1) {
        push_move(move->count - 1, move->spare, move->from, move->to);
    } else if (moves) {
        start_move();
    } else {
        direction = DIR_NONE;
    }
}

void initialize_application() {
    // Fill entire screen with blank characters
    memset(screen_chars, 0x20, sizeof(screen_chars));

    // Write constant texts
    print_at(TITLE_ROW, 0, "===== RVPC Demo =====");
    print_at(STATUS_ROW, 1, "Move #  from   to");

    // Prepare for first move
    push_move(NUM_RINGS, 0, 1, 2);
    delay = STARTUP_DELAY;
    animate_frame();
}

void run_keyboard_state_machine() {
}

void run_app_state_machine() {
    bool redraw;
    Move* move;

    if (v_state == V_STATE_END_FRAME) {
        redraw = false;

        if (delay) {
            delay--;
        } else {
            delay = MOVE_DELAY;
            move = &stack[moves - 1];

            switch (direction) {
                case DIR_NONE: {
                } break;

                case DIR_UP: {
                    if (active_ring->row == FIRST_RING_ROW) {
                        Peg* peg = &pegs[move->from];
                        peg->count--;
                        adjust_peg_columns();
                        if (move->from < move->to) {
                            direction = DIR_RIGHT;
                        } else {
                            direction = DIR_LEFT;
                        }
                    } else {
                        active_ring->row--;
                        redraw = true;
                    }
                } break;

                case DIR_RIGHT: {
                    if (active_ring->col == dest_col) {
                        direction = DIR_DOWN;
                    } else {
                        active_ring->col++;
                        active_ring->start++;
                        active_ring->end++;
                        redraw = true;
                    }
                } break;

                case DIR_DOWN: {
                    if (active_ring->row == dest_row) {
                        active_ring->peg = move->to;
                        Peg* peg = &pegs[move->to];
                        peg->rings[peg->count++] = move->ring;
                        pop_move();
                    } else {
                        active_ring->row++;
                        redraw = true;
                    }
                } break;

                case DIR_LEFT: {
                    if (active_ring->col == dest_col) {
                        direction = DIR_DOWN;
                    } else {
                        active_ring->col--;
                        active_ring->start--;
                        active_ring->end--;
                        redraw = true;
                    }
                } break;
            }
        }
        v_state = V_STATE_FRAME_ACK;
        if (redraw) {
            // Draw the next animation frame (modify array of character codes).
            animate_frame();
        }
    }
}
