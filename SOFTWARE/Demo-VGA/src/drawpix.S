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

    .global   drw8_0x00
    .global   drw8_0x01
    .global   drw8_0x02
    .global   drw8_0x03
    .global   drw8_0x04
    .global   drw8_0x05
    .global   drw8_0x06
    .global   drw8_0x07
    .global   drw8_0x08
    .global   drw8_0x09
    .global   drw8_0x0A
    .global   drw8_0x0B
    .global   drw8_0x0C
    .global   drw8_0x0D
    .global   drw8_0x0E
    .global   drw8_0x0F
    .global   drw8_0x10
    .global   drw8_0x11
    .global   drw8_0x12
    .global   drw8_0x13
    .global   drw8_0x14
    .global   drw8_0x15
    .global   drw8_0x16
    .global   drw8_0x17
    .global   drw8_0x18
    .global   drw8_0x19
    .global   drw8_0x1A
    .global   drw8_0x1B
    .global   drw8_0x1C
    .global   drw8_0x1D
    .global   drw8_0x1E
    .global   drw8_0x1F
    .global   drw8_0x20
    .global   drw8_0x21
    .global   drw8_0x22
    .global   drw8_0x23
    .global   drw8_0x24
    .global   drw8_0x25
    .global   drw8_0x26
    .global   drw8_0x27
    .global   drw8_0x28
    .global   drw8_0x29
    .global   drw8_0x2A
    .global   drw8_0x2B
    .global   drw8_0x2C
    .global   drw8_0x2D
    .global   drw8_0x2E
    .global   drw8_0x2F
    .global   drw8_0x30
    .global   drw8_0x31
    .global   drw8_0x32
    .global   drw8_0x33
    .global   drw8_0x34
    .global   drw8_0x35
    .global   drw8_0x36
    .global   drw8_0x37
    .global   drw8_0x38
    .global   drw8_0x39
    .global   drw8_0x3A
    .global   drw8_0x3B
    .global   drw8_0x3C
    .global   drw8_0x3D
    .global   drw8_0x3E
    .global   drw8_0x3F
    .global   drw8_0x40
    .global   drw8_0x41
    .global   drw8_0x42
    .global   drw8_0x43
    .global   drw8_0x44
    .global   drw8_0x45
    .global   drw8_0x46
    .global   drw8_0x47
    .global   drw8_0x48
    .global   drw8_0x49
    .global   drw8_0x4A
    .global   drw8_0x4B
    .global   drw8_0x4C
    .global   drw8_0x4D
    .global   drw8_0x4E
    .global   drw8_0x4F
    .global   drw8_0x50
    .global   drw8_0x51
    .global   drw8_0x52
    .global   drw8_0x53
    .global   drw8_0x54
    .global   drw8_0x55
    .global   drw8_0x56
    .global   drw8_0x57
    .global   drw8_0x58
    .global   drw8_0x59
    .global   drw8_0x5A
    .global   drw8_0x5B
    .global   drw8_0x5C
    .global   drw8_0x5D
    .global   drw8_0x5E
    .global   drw8_0x5F
    .global   drw8_0x60
    .global   drw8_0x61
    .global   drw8_0x62
    .global   drw8_0x63
    .global   drw8_0x64
    .global   drw8_0x65
    .global   drw8_0x66
    .global   drw8_0x67
    .global   drw8_0x68
    .global   drw8_0x69
    .global   drw8_0x6A
    .global   drw8_0x6B
    .global   drw8_0x6C
    .global   drw8_0x6D
    .global   drw8_0x6E
    .global   drw8_0x6F
    .global   drw8_0x70
    .global   drw8_0x71
    .global   drw8_0x72
    .global   drw8_0x73
    .global   drw8_0x74
    .global   drw8_0x75
    .global   drw8_0x76
    .global   drw8_0x77
    .global   drw8_0x78
    .global   drw8_0x79
    .global   drw8_0x7A
    .global   drw8_0x7B
    .global   drw8_0x7C
    .global   drw8_0x7D
    .global   drw8_0x7E
    .global   drw8_0x7F
    .global   drw8_0x80
    .global   drw8_0x81
    .global   drw8_0x82
    .global   drw8_0x83
    .global   drw8_0x84
    .global   drw8_0x85
    .global   drw8_0x86
    .global   drw8_0x87
    .global   drw8_0x88
    .global   drw8_0x89
    .global   drw8_0x8A
    .global   drw8_0x8B
    .global   drw8_0x8C
    .global   drw8_0x8D
    .global   drw8_0x8E
    .global   drw8_0x8F
    .global   drw8_0x90
    .global   drw8_0x91
    .global   drw8_0x92
    .global   drw8_0x93
    .global   drw8_0x94
    .global   drw8_0x95
    .global   drw8_0x96
    .global   drw8_0x97
    .global   drw8_0x98
    .global   drw8_0x99
    .global   drw8_0x9A
    .global   drw8_0x9B
    .global   drw8_0x9C
    .global   drw8_0x9D
    .global   drw8_0x9E
    .global   drw8_0x9F
    .global   drw8_0xA0
    .global   drw8_0xA1
    .global   drw8_0xA2
    .global   drw8_0xA3
    .global   drw8_0xA4
    .global   drw8_0xA5
    .global   drw8_0xA6
    .global   drw8_0xA7
    .global   drw8_0xA8
    .global   drw8_0xA9
    .global   drw8_0xAA
    .global   drw8_0xAB
    .global   drw8_0xAC
    .global   drw8_0xAD
    .global   drw8_0xAE
    .global   drw8_0xAF
    .global   drw8_0xB0
    .global   drw8_0xB1
    .global   drw8_0xB2
    .global   drw8_0xB3
    .global   drw8_0xB4
    .global   drw8_0xB5
    .global   drw8_0xB6
    .global   drw8_0xB7
    .global   drw8_0xB8
    .global   drw8_0xB9
    .global   drw8_0xBA
    .global   drw8_0xBB
    .global   drw8_0xBC
    .global   drw8_0xBD
    .global   drw8_0xBE
    .global   drw8_0xBF
    .global   drw8_0xC0
    .global   drw8_0xC1
    .global   drw8_0xC2
    .global   drw8_0xC3
    .global   drw8_0xC4
    .global   drw8_0xC5
    .global   drw8_0xC6
    .global   drw8_0xC7
    .global   drw8_0xC8
    .global   drw8_0xC9
    .global   drw8_0xCA
    .global   drw8_0xCB
    .global   drw8_0xCC
    .global   drw8_0xCD
    .global   drw8_0xCE
    .global   drw8_0xCF
    .global   drw8_0xD0
    .global   drw8_0xD1
    .global   drw8_0xD2
    .global   drw8_0xD3
    .global   drw8_0xD4
    .global   drw8_0xD5
    .global   drw8_0xD6
    .global   drw8_0xD7
    .global   drw8_0xD8
    .global   drw8_0xD9
    .global   drw8_0xDA
    .global   drw8_0xDB
    .global   drw8_0xDC
    .global   drw8_0xDD
    .global   drw8_0xDE
    .global   drw8_0xDF
    .global   drw8_0xE0
    .global   drw8_0xE1
    .global   drw8_0xE2
    .global   drw8_0xE3
    .global   drw8_0xE4
    .global   drw8_0xE5
    .global   drw8_0xE6
    .global   drw8_0xE7
    .global   drw8_0xE8
    .global   drw8_0xE9
    .global   drw8_0xEA
    .global   drw8_0xEB
    .global   drw8_0xEC
    .global   drw8_0xED
    .global   drw8_0xEE
    .global   drw8_0xEF
    .global   drw8_0xF0
    .global   drw8_0xF1
    .global   drw8_0xF2
    .global   drw8_0xF3
    .global   drw8_0xF4
    .global   drw8_0xF5
    .global   drw8_0xF6
    .global   drw8_0xF7
    .global   drw8_0xF8
    .global   drw8_0xF9
    .global   drw8_0xFA
    .global   drw8_0xFB
    .global   drw8_0xFC
    .global   drw8_0xFD
    .global   drw8_0xFE
    .global   drw8_0xFF

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

// This function list includes all 8-pixel combinations that
// are actually used in defining characters. Unused functions
// are commented out, to preserve space in flash memory.


    .align 2

draw_pixels:

drw8_0x00:
    PX00
    PX00
    PX00
    PX00
    RT
/*
drw8_0x01:
    PX00
    PX00
    PX00
    PX01
    RT
*/
drw8_0x02:
    PX00
    PX00
    PX00
    PX10
    RT
/*
drw8_0x03:
    PX00
    PX00
    PX00
    PX11
    RT

drw8_0x04:
    PX00
    PX00
    PX01
    PX00
    RT

drw8_0x05:
    PX00
    PX00
    PX01
    PX01
    RT
*/
drw8_0x06:
    PX00
    PX00
    PX01
    PX10
    RT
/*
drw8_0x07:
    PX00
    PX00
    PX01
    PX11
    RT

drw8_0x08:
    PX00
    PX00
    PX10
    PX00
    RT

drw8_0x09:
    PX00
    PX00
    PX10
    PX01
    RT

drw8_0x0A:
    PX00
    PX00
    PX10
    PX10
    RT

drw8_0x0B:
    PX00
    PX00
    PX10
    PX11
    RT
*/
drw8_0x0C:
    PX00
    PX00
    PX11
    PX00
    RT
/*
drw8_0x0D:
    PX00
    PX00
    PX11
    PX01
    RT
*/
drw8_0x0E:
    PX00
    PX00
    PX11
    PX10
    RT
/*
drw8_0x0F:
    PX00
    PX00
    PX11
    PX11
    RT
*/
drw8_0x10:
    PX00
    PX01
    PX00
    PX00
    RT
/*
drw8_0x11:
    PX00
    PX01
    PX00
    PX01
    RT

drw8_0x12:
    PX00
    PX01
    PX00
    PX10
    RT

drw8_0x13:
    PX00
    PX01
    PX00
    PX11
    RT

drw8_0x14:
    PX00
    PX01
    PX01
    PX00
    RT

drw8_0x15:
    PX00
    PX01
    PX01
    PX01
    RT
*/
drw8_0x16:
    PX00
    PX01
    PX01
    PX10
    RT
/*
drw8_0x17:
    PX00
    PX01
    PX01
    PX11
    RT
*/
drw8_0x18:
    PX00
    PX01
    PX10
    PX00
    RT
/*
drw8_0x19:
    PX00
    PX01
    PX10
    PX01
    RT

drw8_0x1A:
    PX00
    PX01
    PX10
    PX10
    RT

drw8_0x1B:
    PX00
    PX01
    PX10
    PX11
    RT
*/
drw8_0x1C:
    PX00
    PX01
    PX11
    PX00
    RT
/*
drw8_0x1D:
    PX00
    PX01
    PX11
    PX01
    RT
*/
drw8_0x1E:
    PX00
    PX01
    PX11
    PX10
    RT
/*
drw8_0x1F:
    PX00
    PX01
    PX11
    PX11
    RT
*/
drw8_0x20:
    PX00
    PX10
    PX00
    PX00
    RT
/*
drw8_0x21:
    PX00
    PX10
    PX00
    PX01
    RT

drw8_0x22:
    PX00
    PX10
    PX00
    PX10
    RT

drw8_0x23:
    PX00
    PX10
    PX00
    PX11
    RT
*/
drw8_0x24:
    PX00
    PX10
    PX01
    PX00
    RT
/*
drw8_0x25:
    PX00
    PX10
    PX01
    PX01
    RT

drw8_0x26:
    PX00
    PX10
    PX01
    PX10
    RT

drw8_0x27:
    PX00
    PX10
    PX01
    PX11
    RT

drw8_0x28:
    PX00
    PX10
    PX10
    PX00
    RT

drw8_0x29:
    PX00
    PX10
    PX10
    PX01
    RT

drw8_0x2A:
    PX00
    PX10
    PX10
    PX10
    RT

drw8_0x2B:
    PX00
    PX10
    PX10
    PX11
    RT

drw8_0x2C:
    PX00
    PX10
    PX11
    PX00
    RT

drw8_0x2D:
    PX00
    PX10
    PX11
    PX01
    RT

drw8_0x2E:
    PX00
    PX10
    PX11
    PX10
    RT

drw8_0x2F:
    PX00
    PX10
    PX11
    PX11
    RT
*/
drw8_0x30:
    PX00
    PX11
    PX00
    PX00
    RT
/*
drw8_0x31:
    PX00
    PX11
    PX00
    PX01
    RT
*/
drw8_0x32:
    PX00
    PX11
    PX00
    PX10
    RT
/*
drw8_0x33:
    PX00
    PX11
    PX00
    PX11
    RT
*/
drw8_0x34:
    PX00
    PX11
    PX01
    PX00
    RT
/*
drw8_0x35:
    PX00
    PX11
    PX01
    PX01
    RT
*/
drw8_0x36:
    PX00
    PX11
    PX01
    PX10
    RT
/*
drw8_0x37:
    PX00
    PX11
    PX01
    PX11
    RT
*/
drw8_0x38:
    PX00
    PX11
    PX10
    PX00
    RT
/*
drw8_0x39:
    PX00
    PX11
    PX10
    PX01
    RT

drw8_0x3A:
    PX00
    PX11
    PX10
    PX10
    RT

drw8_0x3B:
    PX00
    PX11
    PX10
    PX11
    RT
*/
drw8_0x3C:
    PX00
    PX11
    PX11
    PX00
    RT
/*
drw8_0x3D:
    PX00
    PX11
    PX11
    PX01
    RT

drw8_0x3E:
    PX00
    PX11
    PX11
    PX10
    RT

drw8_0x3F:
    PX00
    PX11
    PX11
    PX11
    RT

drw8_0x40:
    PX01
    PX00
    PX00
    PX00
    RT

drw8_0x41:
    PX01
    PX00
    PX00
    PX01
    RT

drw8_0x42:
    PX01
    PX00
    PX00
    PX10
    RT

drw8_0x43:
    PX01
    PX00
    PX00
    PX11
    RT

drw8_0x44:
    PX01
    PX00
    PX01
    PX00
    RT

drw8_0x45:
    PX01
    PX00
    PX01
    PX01
    RT

drw8_0x46:
    PX01
    PX00
    PX01
    PX10
    RT

drw8_0x47:
    PX01
    PX00
    PX01
    PX11
    RT

drw8_0x48:
    PX01
    PX00
    PX10
    PX00
    RT

drw8_0x49:
    PX01
    PX00
    PX10
    PX01
    RT

drw8_0x4A:
    PX01
    PX00
    PX10
    PX10
    RT

drw8_0x4B:
    PX01
    PX00
    PX10
    PX11
    RT
*/
drw8_0x4C:
    PX01
    PX00
    PX11
    PX00
    RT
/*
drw8_0x4D:
    PX01
    PX00
    PX11
    PX01
    RT

drw8_0x4E:
    PX01
    PX00
    PX11
    PX10
    RT

drw8_0x4F:
    PX01
    PX00
    PX11
    PX11
    RT

drw8_0x50:
    PX01
    PX01
    PX00
    PX00
    RT

drw8_0x51:
    PX01
    PX01
    PX00
    PX01
    RT

drw8_0x52:
    PX01
    PX01
    PX00
    PX10
    RT

drw8_0x53:
    PX01
    PX01
    PX00
    PX11
    RT

drw8_0x54:
    PX01
    PX01
    PX01
    PX00
    RT

drw8_0x55:
    PX01
    PX01
    PX01
    PX01
    RT

drw8_0x56:
    PX01
    PX01
    PX01
    PX10
    RT

drw8_0x57:
    PX01
    PX01
    PX01
    PX11
    RT

drw8_0x58:
    PX01
    PX01
    PX10
    PX00
    RT

drw8_0x59:
    PX01
    PX01
    PX10
    PX01
    RT
*/
drw8_0x5A:
    PX01
    PX01
    PX10
    PX10
    RT
/*
drw8_0x5B:
    PX01
    PX01
    PX10
    PX11
    RT

drw8_0x5C:
    PX01
    PX01
    PX11
    PX00
    RT

drw8_0x5D:
    PX01
    PX01
    PX11
    PX01
    RT

drw8_0x5E:
    PX01
    PX01
    PX11
    PX10
    RT

drw8_0x5F:
    PX01
    PX01
    PX11
    PX11
    RT
*/
drw8_0x60:
    PX01
    PX10
    PX00
    PX00
    RT
/*
drw8_0x61:
    PX01
    PX10
    PX00
    PX01
    RT
*/
drw8_0x62:
    PX01
    PX10
    PX00
    PX10
    RT
/*
drw8_0x63:
    PX01
    PX10
    PX00
    PX11
    RT
*/
drw8_0x64:
    PX01
    PX10
    PX01
    PX00
    RT
/*
drw8_0x65:
    PX01
    PX10
    PX01
    PX01
    RT
*/
drw8_0x66:
    PX01
    PX10
    PX01
    PX10
    RT
/*
drw8_0x67:
    PX01
    PX10
    PX01
    PX11
    RT
*/
drw8_0x68:
    PX01
    PX10
    PX10
    PX00
    RT
/*
drw8_0x69:
    PX01
    PX10
    PX10
    PX01
    RT
*/
drw8_0x6A:
    PX01
    PX10
    PX10
    PX10
    RT
/*
drw8_0x6B:
    PX01
    PX10
    PX10
    PX11
    RT
*/
drw8_0x6C:
    PX01
    PX10
    PX11
    PX00
    RT
/*
drw8_0x6D:
    PX01
    PX10
    PX11
    PX01
    RT

drw8_0x6E:
    PX01
    PX10
    PX11
    PX10
    RT

drw8_0x6F:
    PX01
    PX10
    PX11
    PX11
    RT
*/
drw8_0x70:
    PX01
    PX11
    PX00
    PX00
    RT
/*
drw8_0x71:
    PX01
    PX11
    PX00
    PX01
    RT

drw8_0x72:
    PX01
    PX11
    PX00
    PX10
    RT

drw8_0x73:
    PX01
    PX11
    PX00
    PX11
    RT

drw8_0x74:
    PX01
    PX11
    PX01
    PX00
    RT

drw8_0x75:
    PX01
    PX11
    PX01
    PX01
    RT
*/
drw8_0x76:
    PX01
    PX11
    PX01
    PX10
    RT
/*
drw8_0x77:
    PX01
    PX11
    PX01
    PX11
    RT
*/
drw8_0x78:
    PX01
    PX11
    PX10
    PX00
    RT
/*
drw8_0x79:
    PX01
    PX11
    PX10
    PX01
    RT
*/
drw8_0x7A:
    PX01
    PX11
    PX10
    PX10
    RT
/*
drw8_0x7B:
    PX01
    PX11
    PX10
    PX11
    RT
*/
drw8_0x7C:
    PX01
    PX11
    PX11
    PX00
    RT
/*
drw8_0x7D:
    PX01
    PX11
    PX11
    PX01
    RT
*/
drw8_0x7E:
    PX01
    PX11
    PX11
    PX10
    RT
/*
drw8_0x7F:
    PX01
    PX11
    PX11
    PX11
    RT
*/
drw8_0x80:
    PX10
    PX00
    PX00
    PX00
    RT
/*
drw8_0x81:
    PX10
    PX00
    PX00
    PX01
    RT
*/
drw8_0x82:
    PX10
    PX00
    PX00
    PX10
    RT
/*
drw8_0x83:
    PX10
    PX00
    PX00
    PX11
    RT

drw8_0x84:
    PX10
    PX00
    PX01
    PX00
    RT

drw8_0x85:
    PX10
    PX00
    PX01
    PX01
    RT

drw8_0x86:
    PX10
    PX00
    PX01
    PX10
    RT

drw8_0x87:
    PX10
    PX00
    PX01
    PX11
    RT

drw8_0x88:
    PX10
    PX00
    PX10
    PX00
    RT

drw8_0x89:
    PX10
    PX00
    PX10
    PX01
    RT

drw8_0x8A:
    PX10
    PX00
    PX10
    PX10
    RT

drw8_0x8B:
    PX10
    PX00
    PX10
    PX11
    RT
*/
drw8_0x8C:
    PX10
    PX00
    PX11
    PX00
    RT
/*
drw8_0x8D:
    PX10
    PX00
    PX11
    PX01
    RT

drw8_0x8E:
    PX10
    PX00
    PX11
    PX10
    RT

drw8_0x8F:
    PX10
    PX00
    PX11
    PX11
    RT

drw8_0x90:
    PX10
    PX01
    PX00
    PX00
    RT

drw8_0x91:
    PX10
    PX01
    PX00
    PX01
    RT

drw8_0x92:
    PX10
    PX01
    PX00
    PX10
    RT

drw8_0x93:
    PX10
    PX01
    PX00
    PX11
    RT

drw8_0x94:
    PX10
    PX01
    PX01
    PX00
    RT

drw8_0x95:
    PX10
    PX01
    PX01
    PX01
    RT

drw8_0x96:
    PX10
    PX01
    PX01
    PX10
    RT

drw8_0x97:
    PX10
    PX01
    PX01
    PX11
    RT
*/
drw8_0x98:
    PX10
    PX01
    PX10
    PX00
    RT
/*
drw8_0x99:
    PX10
    PX01
    PX10
    PX01
    RT

drw8_0x9A:
    PX10
    PX01
    PX10
    PX10
    RT

drw8_0x9B:
    PX10
    PX01
    PX10
    PX11
    RT

drw8_0x9C:
    PX10
    PX01
    PX11
    PX00
    RT

drw8_0x9D:
    PX10
    PX01
    PX11
    PX01
    RT
*/
drw8_0x9E:
    PX10
    PX01
    PX11
    PX10
    RT
/*
drw8_0x9F:
    PX10
    PX01
    PX11
    PX11
    RT

drw8_0xA0:
    PX10
    PX10
    PX00
    PX00
    RT

drw8_0xA1:
    PX10
    PX10
    PX00
    PX01
    RT

drw8_0xA2:
    PX10
    PX10
    PX00
    PX10
    RT

drw8_0xA3:
    PX10
    PX10
    PX00
    PX11
    RT

drw8_0xA4:
    PX10
    PX10
    PX01
    PX00
    RT

drw8_0xA5:
    PX10
    PX10
    PX01
    PX01
    RT
*/
drw8_0xA6:
    PX10
    PX10
    PX01
    PX10
    RT
/*
drw8_0xA7:
    PX10
    PX10
    PX01
    PX11
    RT

drw8_0xA8:
    PX10
    PX10
    PX10
    PX00
    RT

drw8_0xA9:
    PX10
    PX10
    PX10
    PX01
    RT

drw8_0xAA:
    PX10
    PX10
    PX10
    PX10
    RT

drw8_0xAB:
    PX10
    PX10
    PX10
    PX11
    RT
*/
drw8_0xAC:
    PX10
    PX10
    PX11
    PX00
    RT
/*
drw8_0xAD:
    PX10
    PX10
    PX11
    PX01
    RT

drw8_0xAE:
    PX10
    PX10
    PX11
    PX10
    RT

drw8_0xAF:
    PX10
    PX10
    PX11
    PX11
    RT

drw8_0xB0:
    PX10
    PX11
    PX00
    PX00
    RT

drw8_0xB1:
    PX10
    PX11
    PX00
    PX01
    RT

drw8_0xB2:
    PX10
    PX11
    PX00
    PX10
    RT

drw8_0xB3:
    PX10
    PX11
    PX00
    PX11
    RT

drw8_0xB4:
    PX10
    PX11
    PX01
    PX00
    RT

drw8_0xB5:
    PX10
    PX11
    PX01
    PX01
    RT

drw8_0xB6:
    PX10
    PX11
    PX01
    PX10
    RT

drw8_0xB7:
    PX10
    PX11
    PX01
    PX11
    RT

drw8_0xB8:
    PX10
    PX11
    PX10
    PX00
    RT

drw8_0xB9:
    PX10
    PX11
    PX10
    PX01
    RT

drw8_0xBA:
    PX10
    PX11
    PX10
    PX10
    RT

drw8_0xBB:
    PX10
    PX11
    PX10
    PX11
    RT

drw8_0xBC:
    PX10
    PX11
    PX11
    PX00
    RT

drw8_0xBD:
    PX10
    PX11
    PX11
    PX01
    RT

drw8_0xBE:
    PX10
    PX11
    PX11
    PX10
    RT

drw8_0xBF:
    PX10
    PX11
    PX11
    PX11
    RT
*/
drw8_0xC0:
    PX11
    PX00
    PX00
    PX00
    RT
/*
drw8_0xC1:
    PX11
    PX00
    PX00
    PX01
    RT

drw8_0xC2:
    PX11
    PX00
    PX00
    PX10
    RT

drw8_0xC3:
    PX11
    PX00
    PX00
    PX11
    RT

drw8_0xC4:
    PX11
    PX00
    PX01
    PX00
    RT

drw8_0xC5:
    PX11
    PX00
    PX01
    PX01
    RT
*/
drw8_0xC6:
    PX11
    PX00
    PX01
    PX10
    RT
/*
drw8_0xC7:
    PX11
    PX00
    PX01
    PX11
    RT

drw8_0xC8:
    PX11
    PX00
    PX10
    PX00
    RT

drw8_0xC9:
    PX11
    PX00
    PX10
    PX01
    RT

drw8_0xCA:
    PX11
    PX00
    PX10
    PX10
    RT

drw8_0xCB:
    PX11
    PX00
    PX10
    PX11
    RT
*/
drw8_0xCC:
    PX11
    PX00
    PX11
    PX00
    RT
/*
drw8_0xCD:
    PX11
    PX00
    PX11
    PX01
    RT
*/
drw8_0xCE:
    PX11
    PX00
    PX11
    PX10
    RT
/*
drw8_0xCF:
    PX11
    PX00
    PX11
    PX11
    RT
*/
drw8_0xD0:
    PX11
    PX01
    PX00
    PX00
    RT
/*
drw8_0xD1:
    PX11
    PX01
    PX00
    PX01
    RT

drw8_0xD2:
    PX11
    PX01
    PX00
    PX10
    RT

drw8_0xD3:
    PX11
    PX01
    PX00
    PX11
    RT

drw8_0xD4:
    PX11
    PX01
    PX01
    PX00
    RT

drw8_0xD5:
    PX11
    PX01
    PX01
    PX01
    RT
*/
drw8_0xD6:
    PX11
    PX01
    PX01
    PX10
    RT
/*
drw8_0xD7:
    PX11
    PX01
    PX01
    PX11
    RT
*/
drw8_0xD8:
    PX11
    PX01
    PX10
    PX00
    RT
/*
drw8_0xD9:
    PX11
    PX01
    PX10
    PX01
    RT

drw8_0xDA:
    PX11
    PX01
    PX10
    PX10
    RT

drw8_0xDB:
    PX11
    PX01
    PX10
    PX11
    RT
*/
drw8_0xDC:
    PX11
    PX01
    PX11
    PX00
    RT
/*
drw8_0xDD:
    PX11
    PX01
    PX11
    PX01
    RT
*/
drw8_0xDE:
    PX11
    PX01
    PX11
    PX10
    RT
/*
drw8_0xDF:
    PX11
    PX01
    PX11
    PX11
    RT
*/
drw8_0xE0:
    PX11
    PX10
    PX00
    PX00
    RT
/*
drw8_0xE1:
    PX11
    PX10
    PX00
    PX01
    RT

drw8_0xE2:
    PX11
    PX10
    PX00
    PX10
    RT

drw8_0xE3:
    PX11
    PX10
    PX00
    PX11
    RT

drw8_0xE4:
    PX11
    PX10
    PX01
    PX00
    RT

drw8_0xE5:
    PX11
    PX10
    PX01
    PX01
    RT
*/
drw8_0xE6:
    PX11
    PX10
    PX01
    PX10
    RT
/*
drw8_0xE7:
    PX11
    PX10
    PX01
    PX11
    RT

drw8_0xE8:
    PX11
    PX10
    PX10
    PX00
    RT

drw8_0xE9:
    PX11
    PX10
    PX10
    PX01
    RT

drw8_0xEA:
    PX11
    PX10
    PX10
    PX10
    RT

drw8_0xEB:
    PX11
    PX10
    PX10
    PX11
    RT

drw8_0xEC:
    PX11
    PX10
    PX11
    PX00
    RT

drw8_0xED:
    PX11
    PX10
    PX11
    PX01
    RT
*/
drw8_0xEE:
    PX11
    PX10
    PX11
    PX10
    RT
/*
drw8_0xEF:
    PX11
    PX10
    PX11
    PX11
    RT
*/
drw8_0xF0:
    PX11
    PX11
    PX00
    PX00
    RT
/*
drw8_0xF1:
    PX11
    PX11
    PX00
    PX01
    RT

drw8_0xF2:
    PX11
    PX11
    PX00
    PX10
    RT

drw8_0xF3:
    PX11
    PX11
    PX00
    PX11
    RT

drw8_0xF4:
    PX11
    PX11
    PX01
    PX00
    RT

drw8_0xF5:
    PX11
    PX11
    PX01
    PX01
    RT
*/
drw8_0xF6:
    PX11
    PX11
    PX01
    PX10
    RT
/*
drw8_0xF7:
    PX11
    PX11
    PX01
    PX11
    RT
*/
drw8_0xF8:
    PX11
    PX11
    PX10
    PX00
    RT
/*
drw8_0xF9:
    PX11
    PX11
    PX10
    PX01
    RT

drw8_0xFA:
    PX11
    PX11
    PX10
    PX10
    RT

drw8_0xFB:
    PX11
    PX11
    PX10
    PX11
    RT
*/
drw8_0xFC:
    PX11
    PX11
    PX11
    PX00
    RT
/*
drw8_0xFD:
    PX11
    PX11
    PX11
    PX01
    RT
*/
drw8_0xFE:
    PX11
    PX11
    PX11
    PX10
    RT

drw8_0xFF:
    PX11
    PX11
    PX11
    PX11
    RT

//-----------------------------------------------------------
