// File: rundyn.S
// Purpose: Run dynamic assembler code
// Copyright (c) 2024 by Curtis Whitley
//
// License: Apache
//

#define USE_BSHR    0xC01C  /* c.sw x15,0(x8)   store video-out bit into GPIO BSHR */
#define USE_BCR     0xC09C  /* c.sw x15,0(x9)   store video-out bit into GPIO BCR */

// ZR x0    zero (always)
// RA x1    return address
// SP x2    stack pointer

// a0 x10   ((USE_BCR  << 0) | (USE_BCR  << 16))  pixels __ (0xC09CC09C)
// a1 x11   ((USE_BCR  << 0) | (USE_BSHR << 16))  pixels _* (0xC01CC09C)
// a2 x12   ((USE_BSHR << 0) | (USE_BCR  << 16))  pixels *_ (0xC09CC01C)
// a3 x13   ((USE_BSHR << 0) | (USE_BSHR << 16))  pixels ** (0xC01CC01C)
// a4 x14   address of dynamic code for 1 glyph scan line (8 pixels)
// a5 x15   video-out bit value in GPIO (0x00000004)
// a6 x16
// a7 x17

// s0 x8    address of GPIO BSHR (0x40011010)
// s1 x9    address of GPIO BCR (0x40011014)
// s2 x18
// s3 x19
// s4 x20
// s5 x21
// s6 x22
// s7 x23
// s8 x24
// s9 x25
// s10 x26
// s11 x27

// t0 x5
// t1 x6
// t2 x7
// t3 x28
// t4 x29
// t5 x30
// t6 x31

//-----------------------------------------------------------

    .section .data
    .align 4

    .global   run_dynamic_code
    .global   write_pixels

    .macro PIX_PAIR
    c.sw x15,0(x9)      // clear a pixel
//    c.sw x15,0(x8)      // set a pixel
    c.sw x15,0(x9)      // clear a pixel
    .endm

    .macro WRITE_VIDEO_8
    PIX_PAIR
    PIX_PAIR
    PIX_PAIR
    PIX_PAIR
    .endm

run_dynamic_code:

    mv      x5,x8               // save x8
    mv      x6,x9               // save x9

    li      x8,0x40011010       // load 32 bits of x8 with BSHR address
    // lui     x8,0x40011           // load upper 20 bits of x8 with BSHR address
    // addi    x8,x8,0x010          // load lower 12 bits of x8 with BSHR address

    li      x9,0x40011014       // load upper 20 bits of x9 with BCR address
    // lui     x9,0x40011           // load upper 20 bits of x9 with BCR address
    // addi    x9,x9,0x014          // load lower 12 bits of x9 with BCR address

    addi    x15,x0,4            // load x15 with bit value of video-out

    .align 2

write_pixels:
    WRITE_VIDEO_8 // 00
    WRITE_VIDEO_8 // 01
    WRITE_VIDEO_8 // 02
    WRITE_VIDEO_8 // 03
    WRITE_VIDEO_8 // 04
    WRITE_VIDEO_8 // 05
    WRITE_VIDEO_8 // 06
    WRITE_VIDEO_8 // 07
    WRITE_VIDEO_8 // 08
    WRITE_VIDEO_8 // 09

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
    WRITE_VIDEO_8 // 29

    //WRITE_VIDEO_8 // 30

    mv      x8,x5       // restore x8
    mv      x9,x6       // restore x9
    c.jr    x1          // return from subroutine
