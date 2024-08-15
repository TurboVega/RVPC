// File: drawpix.S
// Purpose: Draw various combinations of pixels
// Copyright (c) 2024 by Curtis Whitley
//
// License: Apache
//

// ZR x0    zero (always)
// RA x1    return address
// SP x2    stack pointer
// a0 x10   video-out bit value in GPIO (0x00000004)
// s0 x8    address of GPIO BSHR (0x40011010)
// s1 x9    address of GPIO BCR (0x40011014)

//-----------------------------------------------------------

    .section .text
    .align 4

    .global   draw_pixels

    // The following are global just so I can see them in the linker map.
    .global   drw8_0x00
    .global   drw8_0x20
    .global   drw8_0x40
    .global   drw8_0x60
    .global   drw8_0x80
    .global   drw8_0xA0
    .global   drw8_0xC0
    .global   drw8_0xE0
    .global   drw8_end

    .macro USE_BSHR
    c.sw x10,0(x8)      // store video-out bit into GPIO BSHR */
    .endm

    .macro USE_BCR
    c.sw x10,0(x9)      // store video-out bit into GPIO BCR */
    .endm

    .macro PX00
    // clear 1st pixel and 2nd pixel
    USE_BCR
    USE_BCR
    .endm

    .macro PX01
    // clear 1st pixel; set 2nd pixel
    USE_BCR
    USE_BSHR
    .endm

    .macro PX10
    // set 1st pixel; clear 2nd pixel
    USE_BSHR
    USE_BCR
    .endm

    .macro PX11
    // set 1st pixel and 2nd pixel
    USE_BSHR
    USE_BSHR
    .endm

    .macro RT
     // return from subroutine
    c.jr x1
    .endm

// The following are 256 separate subroutines, each of which draws
// 8 pixels by writing data to the video-out GPIO port.
// The caller must call the correct function according to the character
// glyph scan line contents (i.e., the 8-bit value of the pixel arrangement
// in a single scan line of a single character glyph).
//

    .align 2

draw_pixels:
drw8_0x00:

    // 0x00
    PX00
    PX00
    PX00
    PX00
    RT

    // 0x01
    PX00
    PX00
    PX00
    PX01
    RT

    // 0x02
    PX00
    PX00
    PX00
    PX10
    RT

    // 0x03
    PX00
    PX00
    PX00
    PX11
    RT

    // 0x04
    PX00
    PX00
    PX01
    PX00
    RT

    // 0x05
    PX00
    PX00
    PX01
    PX01
    RT

    // 0x06
    PX00
    PX00
    PX01
    PX10
    RT

    // 0x07
    PX00
    PX00
    PX01
    PX11
    RT

    // 0x08
    PX00
    PX00
    PX10
    PX00
    RT

    // 0x09
    PX00
    PX00
    PX10
    PX01
    RT

    // 0x0A
    PX00
    PX00
    PX10
    PX10
    RT

    // 0x0B
    PX00
    PX00
    PX10
    PX11
    RT

    // 0x0C
    PX00
    PX00
    PX11
    PX00
    RT

    // 0x0D
    PX00
    PX00
    PX11
    PX01
    RT

    // 0x0E
    PX00
    PX00
    PX11
    PX10
    RT

    // 0x0F
    PX00
    PX00
    PX11
    PX11
    RT

    // 0x10
    PX00
    PX01
    PX00
    PX00
    RT

    // 0x11
    PX00
    PX01
    PX00
    PX01
    RT

    // 0x12
    PX00
    PX01
    PX00
    PX10
    RT

    // 0x13
    PX00
    PX01
    PX00
    PX11
    RT

    // 0x14
    PX00
    PX01
    PX01
    PX00
    RT

    // 0x15
    PX00
    PX01
    PX01
    PX01
    RT

    // 0x16
    PX00
    PX01
    PX01
    PX10
    RT

    // 0x17
    PX00
    PX01
    PX01
    PX11
    RT

    // 0x18
    PX00
    PX01
    PX10
    PX00
    RT

    // 0x19
    PX00
    PX01
    PX10
    PX01
    RT

    // 0x1A
    PX00
    PX01
    PX10
    PX10
    RT

    // 0x1B
    PX00
    PX01
    PX10
    PX11
    RT

    // 0x1C
    PX00
    PX01
    PX11
    PX00
    RT

    // 0x1D
    PX00
    PX01
    PX11
    PX01
    RT

    // 0x1E
    PX00
    PX01
    PX11
    PX10
    RT

    // 0x1F
    PX00
    PX01
    PX11
    PX11
    RT

drw8_0x20:

    // 0x20
    PX00
    PX10
    PX00
    PX00
    RT

    // 0x21
    PX00
    PX10
    PX00
    PX01
    RT

    // 0x22
    PX00
    PX10
    PX00
    PX10
    RT

    // 0x23
    PX00
    PX10
    PX00
    PX11
    RT

    // 0x24
    PX00
    PX10
    PX01
    PX00
    RT

    // 0x25
    PX00
    PX10
    PX01
    PX01
    RT

    // 0x26
    PX00
    PX10
    PX01
    PX10
    RT

    // 0x27
    PX00
    PX10
    PX01
    PX11
    RT

    // 0x28
    PX00
    PX10
    PX10
    PX00
    RT

    // 0x29
    PX00
    PX10
    PX10
    PX01
    RT

    // 0x2A
    PX00
    PX10
    PX10
    PX10
    RT

    // 0x2B
    PX00
    PX10
    PX10
    PX11
    RT

    // 0x2C
    PX00
    PX10
    PX11
    PX00
    RT

    // 0x2D
    PX00
    PX10
    PX11
    PX01
    RT

    // 0x2E
    PX00
    PX10
    PX11
    PX10
    RT

    // 0x2F
    PX00
    PX10
    PX11
    PX11
    RT

    // 0x30
    PX00
    PX11
    PX00
    PX00
    RT

    // 0x31
    PX00
    PX11
    PX00
    PX01
    RT

    // 0x32
    PX00
    PX11
    PX00
    PX10
    RT

    // 0x33
    PX00
    PX11
    PX00
    PX11
    RT

    // 0x34
    PX00
    PX11
    PX01
    PX00
    RT

    // 0x35
    PX00
    PX11
    PX01
    PX01
    RT

    // 0x36
    PX00
    PX11
    PX01
    PX10
    RT

    // 0x37
    PX00
    PX11
    PX01
    PX11
    RT

    // 0x38
    PX00
    PX11
    PX10
    PX00
    RT

    // 0x39
    PX00
    PX11
    PX10
    PX01
    RT

    // 0x3A
    PX00
    PX11
    PX10
    PX10
    RT

    // 0x3B
    PX00
    PX11
    PX10
    PX11
    RT

    // 0x3C
    PX00
    PX11
    PX11
    PX00
    RT

    // 0x3D
    PX00
    PX11
    PX11
    PX01
    RT

    // 0x3E
    PX00
    PX11
    PX11
    PX10
    RT

    // 0x3F
    PX00
    PX11
    PX11
    PX11
    RT

drw8_0x40:

    // 0x40
    PX01
    PX00
    PX00
    PX00
    RT

    // 0x41
    PX01
    PX00
    PX00
    PX01
    RT

    // 0x42
    PX01
    PX00
    PX00
    PX10
    RT

    // 0x43
    PX01
    PX00
    PX00
    PX11
    RT

    // 0x44
    PX01
    PX00
    PX01
    PX00
    RT

    // 0x45
    PX01
    PX00
    PX01
    PX01
    RT

    // 0x46
    PX01
    PX00
    PX01
    PX10
    RT

    // 0x47
    PX01
    PX00
    PX01
    PX11
    RT

    // 0x48
    PX01
    PX00
    PX10
    PX00
    RT

    // 0x49
    PX01
    PX00
    PX10
    PX01
    RT

    // 0x4A
    PX01
    PX00
    PX10
    PX10
    RT

    // 0x4B
    PX01
    PX00
    PX10
    PX11
    RT

    // 0x4C
    PX01
    PX00
    PX11
    PX00
    RT

    // 0x4D
    PX01
    PX00
    PX11
    PX01
    RT

    // 0x4E
    PX01
    PX00
    PX11
    PX10
    RT

    // 0x4F
    PX01
    PX00
    PX11
    PX11
    RT

    // 0x50
    PX01
    PX01
    PX00
    PX00
    RT

    // 0x51
    PX01
    PX01
    PX00
    PX01
    RT

    // 0x52
    PX01
    PX01
    PX00
    PX10
    RT

    // 0x53
    PX01
    PX01
    PX00
    PX11
    RT

    // 0x54
    PX01
    PX01
    PX01
    PX00
    RT

    // 0x55
    PX01
    PX01
    PX01
    PX01
    RT

    // 0x56
    PX01
    PX01
    PX01
    PX10
    RT

    // 0x57
    PX01
    PX01
    PX01
    PX11
    RT

    // 0x58
    PX01
    PX01
    PX10
    PX00
    RT

    // 0x59
    PX01
    PX01
    PX10
    PX01
    RT

    // 0x5A
    PX01
    PX01
    PX10
    PX10
    RT

    // 0x5B
    PX01
    PX01
    PX10
    PX11
    RT

    // 0x5C
    PX01
    PX01
    PX11
    PX00
    RT

    // 0x5D
    PX01
    PX01
    PX11
    PX01
    RT

    // 0x5E
    PX01
    PX01
    PX11
    PX10
    RT

    // 0x5F
    PX01
    PX01
    PX11
    PX11
    RT

drw8_0x60:

    // 0x60
    PX01
    PX10
    PX00
    PX00
    RT

    // 0x61
    PX01
    PX10
    PX00
    PX01
    RT

    // 0x62
    PX01
    PX10
    PX00
    PX10
    RT

    // 0x63
    PX01
    PX10
    PX00
    PX11
    RT

    // 0x64
    PX01
    PX10
    PX01
    PX00
    RT

    // 0x65
    PX01
    PX10
    PX01
    PX01
    RT

    // 0x66
    PX01
    PX10
    PX01
    PX10
    RT

    // 0x67
    PX01
    PX10
    PX01
    PX11
    RT

    // 0x68
    PX01
    PX10
    PX10
    PX00
    RT

    // 0x69
    PX01
    PX10
    PX10
    PX01
    RT

    // 0x6A
    PX01
    PX10
    PX10
    PX10
    RT

    // 0x6B
    PX01
    PX10
    PX10
    PX11
    RT

    // 0x6C
    PX01
    PX10
    PX11
    PX00
    RT

    // 0x6D
    PX01
    PX10
    PX11
    PX01
    RT

    // 0x6E
    PX01
    PX10
    PX11
    PX10
    RT

    // 0x6F
    PX01
    PX10
    PX11
    PX11
    RT

    // 0x70
    PX01
    PX11
    PX00
    PX00
    RT

    // 0x71
    PX01
    PX11
    PX00
    PX01
    RT

    // 0x72
    PX01
    PX11
    PX00
    PX10
    RT

    // 0x73
    PX01
    PX11
    PX00
    PX11
    RT

    // 0x74
    PX01
    PX11
    PX01
    PX00
    RT

    // 0x75
    PX01
    PX11
    PX01
    PX01
    RT

    // 0x76
    PX01
    PX11
    PX01
    PX10
    RT

    // 0x77
    PX01
    PX11
    PX01
    PX11
    RT

    // 0x78
    PX01
    PX11
    PX10
    PX00
    RT

    // 0x79
    PX01
    PX11
    PX10
    PX01
    RT

    // 0x7A
    PX01
    PX11
    PX10
    PX10
    RT

    // 0x7B
    PX01
    PX11
    PX10
    PX11
    RT

    // 0x7C
    PX01
    PX11
    PX11
    PX00
    RT

    // 0x7D
    PX01
    PX11
    PX11
    PX01
    RT

    // 0x7E
    PX01
    PX11
    PX11
    PX10
    RT

    // 0x7F
    PX01
    PX11
    PX11
    PX11
    RT

drw8_0x80:

    // 0x80
    PX10
    PX00
    PX00
    PX00
    RT

    // 0x81
    PX10
    PX00
    PX00
    PX01
    RT

    // 0x82
    PX10
    PX00
    PX00
    PX10
    RT

    // 0x83
    PX10
    PX00
    PX00
    PX11
    RT

    // 0x84
    PX10
    PX00
    PX01
    PX00
    RT

    // 0x85
    PX10
    PX00
    PX01
    PX01
    RT

    // 0x86
    PX10
    PX00
    PX01
    PX10
    RT

    // 0x87
    PX10
    PX00
    PX01
    PX11
    RT

    // 0x88
    PX10
    PX00
    PX10
    PX00
    RT

    // 0x89
    PX10
    PX00
    PX10
    PX01
    RT

    // 0x8A
    PX10
    PX00
    PX10
    PX10
    RT

    // 0x8B
    PX10
    PX00
    PX10
    PX11
    RT

    // 0x8C
    PX10
    PX00
    PX11
    PX00
    RT

    // 0x8D
    PX10
    PX00
    PX11
    PX01
    RT

    // 0x8E
    PX10
    PX00
    PX11
    PX10
    RT

    // 0x8F
    PX10
    PX00
    PX11
    PX11
    RT

    // 0x90
    PX10
    PX01
    PX00
    PX00
    RT

    // 0x91
    PX10
    PX01
    PX00
    PX01
    RT

    // 0x92
    PX10
    PX01
    PX00
    PX10
    RT

    // 0x93
    PX10
    PX01
    PX00
    PX11
    RT

    // 0x94
    PX10
    PX01
    PX01
    PX00
    RT

    // 0x95
    PX10
    PX01
    PX01
    PX01
    RT

    // 0x96
    PX10
    PX01
    PX01
    PX10
    RT

    // 0x97
    PX10
    PX01
    PX01
    PX11
    RT

    // 0x98
    PX10
    PX01
    PX10
    PX00
    RT

    // 0x99
    PX10
    PX01
    PX10
    PX01
    RT

    // 0x9A
    PX10
    PX01
    PX10
    PX10
    RT

    // 0x9B
    PX10
    PX01
    PX10
    PX11
    RT

    // 0x9C
    PX10
    PX01
    PX11
    PX00
    RT

    // 0x9D
    PX10
    PX01
    PX11
    PX01
    RT

    // 0x9E
    PX10
    PX01
    PX11
    PX10
    RT

    // 0x9F
    PX10
    PX01
    PX11
    PX11
    RT

drw8_0xA0:

    // 0xA0
    PX10
    PX10
    PX00
    PX00
    RT

    // 0xA1
    PX10
    PX10
    PX00
    PX01
    RT

    // 0xA2
    PX10
    PX10
    PX00
    PX10
    RT

    // 0xA3
    PX10
    PX10
    PX00
    PX11
    RT

    // 0xA4
    PX10
    PX10
    PX01
    PX00
    RT

    // 0xA5
    PX10
    PX10
    PX01
    PX01
    RT

    // 0xA6
    PX10
    PX10
    PX01
    PX10
    RT

    // 0xA7
    PX10
    PX10
    PX01
    PX11
    RT

    // 0xA8
    PX10
    PX10
    PX10
    PX00
    RT

    // 0xA9
    PX10
    PX10
    PX10
    PX01
    RT

    // 0xAA
    PX10
    PX10
    PX10
    PX10
    RT

    // 0xAB
    PX10
    PX10
    PX10
    PX11
    RT

    // 0xAC
    PX10
    PX10
    PX11
    PX00
    RT

    // 0xAD
    PX10
    PX10
    PX11
    PX01
    RT

    // 0xAE
    PX10
    PX10
    PX11
    PX10
    RT

    // 0xAF
    PX10
    PX10
    PX11
    PX11
    RT

    // 0xB0
    PX10
    PX11
    PX00
    PX00
    RT

    // 0xB1
    PX10
    PX11
    PX00
    PX01
    RT

    // 0xB2
    PX10
    PX11
    PX00
    PX10
    RT

    // 0xB3
    PX10
    PX11
    PX00
    PX11
    RT

    // 0xB4
    PX10
    PX11
    PX01
    PX00
    RT

    // 0xB5
    PX10
    PX11
    PX01
    PX01
    RT

    // 0xB6
    PX10
    PX11
    PX01
    PX10
    RT

    // 0xB7
    PX10
    PX11
    PX01
    PX11
    RT

    // 0xB8
    PX10
    PX11
    PX10
    PX00
    RT

    // 0xB9
    PX10
    PX11
    PX10
    PX01
    RT

    // 0xBA
    PX10
    PX11
    PX10
    PX10
    RT

    // 0xBB
    PX10
    PX11
    PX10
    PX11
    RT

    // 0xBC
    PX10
    PX11
    PX11
    PX00
    RT

    // 0xBD
    PX10
    PX11
    PX11
    PX01
    RT

    // 0xBE
    PX10
    PX11
    PX11
    PX10
    RT

    // 0xBF
    PX10
    PX11
    PX11
    PX11
    RT

drw8_0xC0:

    // 0xC0
    PX11
    PX00
    PX00
    PX00
    RT

    // 0xC1
    PX11
    PX00
    PX00
    PX01
    RT

    // 0xC2
    PX11
    PX00
    PX00
    PX10
    RT

    // 0xC3
    PX11
    PX00
    PX00
    PX11
    RT

    // 0xC4
    PX11
    PX00
    PX01
    PX00
    RT

    // 0xC5
    PX11
    PX00
    PX01
    PX01
    RT

    // 0xC6
    PX11
    PX00
    PX01
    PX10
    RT

    // 0xC7
    PX11
    PX00
    PX01
    PX11
    RT

    // 0xC8
    PX11
    PX00
    PX10
    PX00
    RT

    // 0xC9
    PX11
    PX00
    PX10
    PX01
    RT

    // 0xCA
    PX11
    PX00
    PX10
    PX10
    RT

    // 0xCB
    PX11
    PX00
    PX10
    PX11
    RT

    // 0xCC
    PX11
    PX00
    PX11
    PX00
    RT

    // 0xCD
    PX11
    PX00
    PX11
    PX01
    RT

    // 0xCE
    PX11
    PX00
    PX11
    PX10
    RT

    // 0xCF
    PX11
    PX00
    PX11
    PX11
    RT

    // 0xD0
    PX11
    PX01
    PX00
    PX00
    RT

    // 0xD1
    PX11
    PX01
    PX00
    PX01
    RT

    // 0xD2
    PX11
    PX01
    PX00
    PX10
    RT

    // 0xD3
    PX11
    PX01
    PX00
    PX11
    RT

    // 0xD4
    PX11
    PX01
    PX01
    PX00
    RT

    // 0xD5
    PX11
    PX01
    PX01
    PX01
    RT

    // 0xD6
    PX11
    PX01
    PX01
    PX10
    RT

    // 0xD7
    PX11
    PX01
    PX01
    PX11
    RT

    // 0xD8
    PX11
    PX01
    PX10
    PX00
    RT

    // 0xD9
    PX11
    PX01
    PX10
    PX01
    RT

    // 0xDA
    PX11
    PX01
    PX10
    PX10
    RT

    // 0xDB
    PX11
    PX01
    PX10
    PX11
    RT

    // 0xDC
    PX11
    PX01
    PX11
    PX00
    RT

    // 0xDD
    PX11
    PX01
    PX11
    PX01
    RT

    // 0xDE
    PX11
    PX01
    PX11
    PX10
    RT

    // 0xDF
    PX11
    PX01
    PX11
    PX11
    RT

drw8_0xE0:

    // 0xE0
    PX11
    PX10
    PX00
    PX00
    RT

    // 0xE1
    PX11
    PX10
    PX00
    PX01
    RT

    // 0xE2
    PX11
    PX10
    PX00
    PX10
    RT

    // 0xE3
    PX11
    PX10
    PX00
    PX11
    RT

    // 0xE4
    PX11
    PX10
    PX01
    PX00
    RT

    // 0xE5
    PX11
    PX10
    PX01
    PX01
    RT

    // 0xE6
    PX11
    PX10
    PX01
    PX10
    RT

    // 0xE7
    PX11
    PX10
    PX01
    PX11
    RT

    // 0xE8
    PX11
    PX10
    PX10
    PX00
    RT

    // 0xE9
    PX11
    PX10
    PX10
    PX01
    RT

    // 0xEA
    PX11
    PX10
    PX10
    PX10
    RT

    // 0xEB
    PX11
    PX10
    PX10
    PX11
    RT

    // 0xEC
    PX11
    PX10
    PX11
    PX00
    RT

    // 0xED
    PX11
    PX10
    PX11
    PX01
    RT

    // 0xEE
    PX11
    PX10
    PX11
    PX10
    RT

    // 0xEF
    PX11
    PX10
    PX11
    PX11
    RT

    // 0xF0
    PX11
    PX11
    PX00
    PX00
    RT

    // 0xF1
    PX11
    PX11
    PX00
    PX01
    RT

    // 0xF2
    PX11
    PX11
    PX00
    PX10
    RT

    // 0xF3
    PX11
    PX11
    PX00
    PX11
    RT

    // 0xF4
    PX11
    PX11
    PX01
    PX00
    RT

    // 0xF5
    PX11
    PX11
    PX01
    PX01
    RT

    // 0xF6
    PX11
    PX11
    PX01
    PX10
    RT

    // 0xF7
    PX11
    PX11
    PX01
    PX11
    RT

    // 0xF8
    PX11
    PX11
    PX10
    PX00
    RT

    // 0xF9
    PX11
    PX11
    PX10
    PX01
    RT

    // 0xFA
    PX11
    PX11
    PX10
    PX10
    RT

    // 0xFB
    PX11
    PX11
    PX10
    PX11
    RT

    // 0xFC
    PX11
    PX11
    PX11
    PX00
    RT

    // 0xFD
    PX11
    PX11
    PX11
    PX01
    RT

    // 0xFE
    PX11
    PX11
    PX11
    PX10
    RT

    // 0xFF
    PX11
    PX11
    PX11
    PX11
    RT

drw8_end:
