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

    .extern   drw8_0x00
    .extern   drw8_0x01
    .extern   drw8_0x02
    .extern   drw8_0x03
    .extern   drw8_0x04
    .extern   drw8_0x05
    .extern   drw8_0x06
    .extern   drw8_0x07
    .extern   drw8_0x08
    .extern   drw8_0x09
    .extern   drw8_0x0A
    .extern   drw8_0x0B
    .extern   drw8_0x0C
    .extern   drw8_0x0D
    .extern   drw8_0x0E
    .extern   drw8_0x0F
    .extern   drw8_0x10
    .extern   drw8_0x11
    .extern   drw8_0x12
    .extern   drw8_0x13
    .extern   drw8_0x14
    .extern   drw8_0x15
    .extern   drw8_0x16
    .extern   drw8_0x17
    .extern   drw8_0x18
    .extern   drw8_0x19
    .extern   drw8_0x1A
    .extern   drw8_0x1B
    .extern   drw8_0x1C
    .extern   drw8_0x1D
    .extern   drw8_0x1E
    .extern   drw8_0x1F
    .extern   drw8_0x20
    .extern   drw8_0x21
    .extern   drw8_0x22
    .extern   drw8_0x23
    .extern   drw8_0x24
    .extern   drw8_0x25
    .extern   drw8_0x26
    .extern   drw8_0x27
    .extern   drw8_0x28
    .extern   drw8_0x29
    .extern   drw8_0x2A
    .extern   drw8_0x2B
    .extern   drw8_0x2C
    .extern   drw8_0x2D
    .extern   drw8_0x2E
    .extern   drw8_0x2F
    .extern   drw8_0x30
    .extern   drw8_0x31
    .extern   drw8_0x32
    .extern   drw8_0x33
    .extern   drw8_0x34
    .extern   drw8_0x35
    .extern   drw8_0x36
    .extern   drw8_0x37
    .extern   drw8_0x38
    .extern   drw8_0x39
    .extern   drw8_0x3A
    .extern   drw8_0x3B
    .extern   drw8_0x3C
    .extern   drw8_0x3D
    .extern   drw8_0x3E
    .extern   drw8_0x3F
    .extern   drw8_0x40
    .extern   drw8_0x41
    .extern   drw8_0x42
    .extern   drw8_0x43
    .extern   drw8_0x44
    .extern   drw8_0x45
    .extern   drw8_0x46
    .extern   drw8_0x47
    .extern   drw8_0x48
    .extern   drw8_0x49
    .extern   drw8_0x4A
    .extern   drw8_0x4B
    .extern   drw8_0x4C
    .extern   drw8_0x4D
    .extern   drw8_0x4E
    .extern   drw8_0x4F
    .extern   drw8_0x50
    .extern   drw8_0x51
    .extern   drw8_0x52
    .extern   drw8_0x53
    .extern   drw8_0x54
    .extern   drw8_0x55
    .extern   drw8_0x56
    .extern   drw8_0x57
    .extern   drw8_0x58
    .extern   drw8_0x59
    .extern   drw8_0x5A
    .extern   drw8_0x5B
    .extern   drw8_0x5C
    .extern   drw8_0x5D
    .extern   drw8_0x5E
    .extern   drw8_0x5F
    .extern   drw8_0x60
    .extern   drw8_0x61
    .extern   drw8_0x62
    .extern   drw8_0x63
    .extern   drw8_0x64
    .extern   drw8_0x65
    .extern   drw8_0x66
    .extern   drw8_0x67
    .extern   drw8_0x68
    .extern   drw8_0x69
    .extern   drw8_0x6A
    .extern   drw8_0x6B
    .extern   drw8_0x6C
    .extern   drw8_0x6D
    .extern   drw8_0x6E
    .extern   drw8_0x6F
    .extern   drw8_0x70
    .extern   drw8_0x71
    .extern   drw8_0x72
    .extern   drw8_0x73
    .extern   drw8_0x74
    .extern   drw8_0x75
    .extern   drw8_0x76
    .extern   drw8_0x77
    .extern   drw8_0x78
    .extern   drw8_0x79
    .extern   drw8_0x7A
    .extern   drw8_0x7B
    .extern   drw8_0x7C
    .extern   drw8_0x7D
    .extern   drw8_0x7E
    .extern   drw8_0x7F
    .extern   drw8_0x80
    .extern   drw8_0x81
    .extern   drw8_0x82
    .extern   drw8_0x83
    .extern   drw8_0x84
    .extern   drw8_0x85
    .extern   drw8_0x86
    .extern   drw8_0x87
    .extern   drw8_0x88
    .extern   drw8_0x89
    .extern   drw8_0x8A
    .extern   drw8_0x8B
    .extern   drw8_0x8C
    .extern   drw8_0x8D
    .extern   drw8_0x8E
    .extern   drw8_0x8F
    .extern   drw8_0x90
    .extern   drw8_0x91
    .extern   drw8_0x92
    .extern   drw8_0x93
    .extern   drw8_0x94
    .extern   drw8_0x95
    .extern   drw8_0x96
    .extern   drw8_0x97
    .extern   drw8_0x98
    .extern   drw8_0x99
    .extern   drw8_0x9A
    .extern   drw8_0x9B
    .extern   drw8_0x9C
    .extern   drw8_0x9D
    .extern   drw8_0x9E
    .extern   drw8_0x9F
    .extern   drw8_0xA0
    .extern   drw8_0xA1
    .extern   drw8_0xA2
    .extern   drw8_0xA3
    .extern   drw8_0xA4
    .extern   drw8_0xA5
    .extern   drw8_0xA6
    .extern   drw8_0xA7
    .extern   drw8_0xA8
    .extern   drw8_0xA9
    .extern   drw8_0xAA
    .extern   drw8_0xAB
    .extern   drw8_0xAC
    .extern   drw8_0xAD
    .extern   drw8_0xAE
    .extern   drw8_0xAF
    .extern   drw8_0xB0
    .extern   drw8_0xB1
    .extern   drw8_0xB2
    .extern   drw8_0xB3
    .extern   drw8_0xB4
    .extern   drw8_0xB5
    .extern   drw8_0xB6
    .extern   drw8_0xB7
    .extern   drw8_0xB8
    .extern   drw8_0xB9
    .extern   drw8_0xBA
    .extern   drw8_0xBB
    .extern   drw8_0xBC
    .extern   drw8_0xBD
    .extern   drw8_0xBE
    .extern   drw8_0xBF
    .extern   drw8_0xC0
    .extern   drw8_0xC1
    .extern   drw8_0xC2
    .extern   drw8_0xC3
    .extern   drw8_0xC4
    .extern   drw8_0xC5
    .extern   drw8_0xC6
    .extern   drw8_0xC7
    .extern   drw8_0xC8
    .extern   drw8_0xC9
    .extern   drw8_0xCA
    .extern   drw8_0xCB
    .extern   drw8_0xCC
    .extern   drw8_0xCD
    .extern   drw8_0xCE
    .extern   drw8_0xCF
    .extern   drw8_0xD0
    .extern   drw8_0xD1
    .extern   drw8_0xD2
    .extern   drw8_0xD3
    .extern   drw8_0xD4
    .extern   drw8_0xD5
    .extern   drw8_0xD6
    .extern   drw8_0xD7
    .extern   drw8_0xD8
    .extern   drw8_0xD9
    .extern   drw8_0xDA
    .extern   drw8_0xDB
    .extern   drw8_0xDC
    .extern   drw8_0xDD
    .extern   drw8_0xDE
    .extern   drw8_0xDF
    .extern   drw8_0xE0
    .extern   drw8_0xE1
    .extern   drw8_0xE2
    .extern   drw8_0xE3
    .extern   drw8_0xE4
    .extern   drw8_0xE5
    .extern   drw8_0xE6
    .extern   drw8_0xE7
    .extern   drw8_0xE8
    .extern   drw8_0xE9
    .extern   drw8_0xEA
    .extern   drw8_0xEB
    .extern   drw8_0xEC
    .extern   drw8_0xED
    .extern   drw8_0xEE
    .extern   drw8_0xEF
    .extern   drw8_0xF0
    .extern   drw8_0xF1
    .extern   drw8_0xF2
    .extern   drw8_0xF3
    .extern   drw8_0xF4
    .extern   drw8_0xF5
    .extern   drw8_0xF6
    .extern   drw8_0xF7
    .extern   drw8_0xF8
    .extern   drw8_0xF9
    .extern   drw8_0xFA
    .extern   drw8_0xFB
    .extern   drw8_0xFC
    .extern   drw8_0xFD
    .extern   drw8_0xFE
    .extern   drw8_0xFF

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
    PX00
    PX00
    PX00
    PX00
    RT

drw8_0x01:
    PX00
    PX00
    PX00
    PX01
    RT

drw8_0x02:
    PX00
    PX00
    PX00
    PX10
    RT

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

drw8_0x06:
    PX00
    PX00
    PX01
    PX10
    RT

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

drw8_0x0C:
    PX00
    PX00
    PX11
    PX00
    RT

drw8_0x0D:
    PX00
    PX00
    PX11
    PX01
    RT

drw8_0x0E:
    PX00
    PX00
    PX11
    PX10
    RT

drw8_0x0F:
    PX00
    PX00
    PX11
    PX11
    RT

drw8_0x10:
    PX00
    PX01
    PX00
    PX00
    RT

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

drw8_0x16:
    PX00
    PX01
    PX01
    PX10
    RT

drw8_0x17:
    PX00
    PX01
    PX01
    PX11
    RT

drw8_0x18:
    PX00
    PX01
    PX10
    PX00
    RT

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

drw8_0x1C:
    PX00
    PX01
    PX11
    PX00
    RT

drw8_0x1D:
    PX00
    PX01
    PX11
    PX01
    RT

drw8_0x1E:
    PX00
    PX01
    PX11
    PX10
    RT

drw8_0x1F:
    PX00
    PX01
    PX11
    PX11
    RT

drw8_0x20:
    PX00
    PX10
    PX00
    PX00
    RT

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

drw8_0x24:
    PX00
    PX10
    PX01
    PX00
    RT

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

drw8_0x30:
    PX00
    PX11
    PX00
    PX00
    RT

drw8_0x31:
    PX00
    PX11
    PX00
    PX01
    RT

drw8_0x32:
    PX00
    PX11
    PX00
    PX10
    RT

drw8_0x33:
    PX00
    PX11
    PX00
    PX11
    RT

drw8_0x34:
    PX00
    PX11
    PX01
    PX00
    RT

drw8_0x35:
    PX00
    PX11
    PX01
    PX01
    RT

drw8_0x36:
    PX00
    PX11
    PX01
    PX10
    RT

drw8_0x37:
    PX00
    PX11
    PX01
    PX11
    RT

drw8_0x38:
    PX00
    PX11
    PX10
    PX00
    RT

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

drw8_0x3C:
    PX00
    PX11
    PX11
    PX00
    RT

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

drw8_0x4C:
    PX01
    PX00
    PX11
    PX00
    RT

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

drw8_0x5A:
    PX01
    PX01
    PX10
    PX10
    RT

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

drw8_0x60:
    PX01
    PX10
    PX00
    PX00
    RT

drw8_0x61:
    PX01
    PX10
    PX00
    PX01
    RT

drw8_0x62:
    PX01
    PX10
    PX00
    PX10
    RT

drw8_0x63:
    PX01
    PX10
    PX00
    PX11
    RT

drw8_0x64:
    PX01
    PX10
    PX01
    PX00
    RT

drw8_0x65:
    PX01
    PX10
    PX01
    PX01
    RT

drw8_0x66:
    PX01
    PX10
    PX01
    PX10
    RT

drw8_0x67:
    PX01
    PX10
    PX01
    PX11
    RT

drw8_0x68:
    PX01
    PX10
    PX10
    PX00
    RT

drw8_0x69:
    PX01
    PX10
    PX10
    PX01
    RT

drw8_0x6A:
    PX01
    PX10
    PX10
    PX10
    RT

drw8_0x6B:
    PX01
    PX10
    PX10
    PX11
    RT

drw8_0x6C:
    PX01
    PX10
    PX11
    PX00
    RT

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

drw8_0x70:
    PX01
    PX11
    PX00
    PX00
    RT

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

drw8_0x76:
    PX01
    PX11
    PX01
    PX10
    RT

drw8_0x77:
    PX01
    PX11
    PX01
    PX11
    RT

drw8_0x78:
    PX01
    PX11
    PX10
    PX00
    RT

drw8_0x79:
    PX01
    PX11
    PX10
    PX01
    RT

drw8_0x7A:
    PX01
    PX11
    PX10
    PX10
    RT

drw8_0x7B:
    PX01
    PX11
    PX10
    PX11
    RT

drw8_0x7C:
    PX01
    PX11
    PX11
    PX00
    RT

drw8_0x7D:
    PX01
    PX11
    PX11
    PX01
    RT

drw8_0x7E:
    PX01
    PX11
    PX11
    PX10
    RT

drw8_0x7F:
    PX01
    PX11
    PX11
    PX11
    RT

drw8_0x80:
    PX10
    PX00
    PX00
    PX00
    RT

drw8_0x81:
    PX10
    PX00
    PX00
    PX01
    RT

drw8_0x82:
    PX10
    PX00
    PX00
    PX10
    RT

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

drw8_0x8C:
    PX10
    PX00
    PX11
    PX00
    RT

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

drw8_0x98:
    PX10
    PX01
    PX10
    PX00
    RT

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

drw8_0x9E:
    PX10
    PX01
    PX11
    PX10
    RT

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

drw8_0xA6:
    PX10
    PX10
    PX01
    PX10
    RT

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

drw8_0xAC:
    PX10
    PX10
    PX11
    PX00
    RT

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

drw8_0xC0:
    PX11
    PX00
    PX00
    PX00
    RT

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

drw8_0xC6:
    PX11
    PX00
    PX01
    PX10
    RT

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

drw8_0xCC:
    PX11
    PX00
    PX11
    PX00
    RT

drw8_0xCD:
    PX11
    PX00
    PX11
    PX01
    RT

drw8_0xCE:
    PX11
    PX00
    PX11
    PX10
    RT

drw8_0xCF:
    PX11
    PX00
    PX11
    PX11
    RT

drw8_0xD0:
    PX11
    PX01
    PX00
    PX00
    RT

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

drw8_0xD6:
    PX11
    PX01
    PX01
    PX10
    RT

drw8_0xD7:
    PX11
    PX01
    PX01
    PX11
    RT

drw8_0xD8:
    PX11
    PX01
    PX10
    PX00
    RT

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

drw8_0xDC:
    PX11
    PX01
    PX11
    PX00
    RT

drw8_0xDD:
    PX11
    PX01
    PX11
    PX01
    RT

drw8_0xDE:
    PX11
    PX01
    PX11
    PX10
    RT

drw8_0xDF:
    PX11
    PX01
    PX11
    PX11
    RT

drw8_0xE0:
    PX11
    PX10
    PX00
    PX00
    RT

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

drw8_0xE6:
    PX11
    PX10
    PX01
    PX10
    RT

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

drw8_0xEE:
    PX11
    PX10
    PX11
    PX10
    RT

drw8_0xEF:
    PX11
    PX10
    PX11
    PX11
    RT

drw8_0xF0:
    PX11
    PX11
    PX00
    PX00
    RT

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

drw8_0xF6:
    PX11
    PX11
    PX01
    PX10
    RT

drw8_0xF7:
    PX11
    PX11
    PX01
    PX11
    RT

drw8_0xF8:
    PX11
    PX11
    PX10
    PX00
    RT

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

drw8_0xFC:
    PX11
    PX11
    PX11
    PX00
    RT

drw8_0xFD:
    PX11
    PX11
    PX11
    PX01
    RT

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
