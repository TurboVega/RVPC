// File: waste.S
// Purpose: Waste time (loop)
// Copyright (c) 2024 by Curtis Whitley
//
// License: Apache
//

//-----------------------------------------------------------

    .section .text
    .align 4

    .global waste_time0
    .global waste_time1

waste_time1:

    nop                         // delay 1 instruction and fall thru

waste_time0:

    addi    x5,x0,20            // load delay loop count

waste_loop:

    addi    x5,x5,-1            // decrease count
    bne     x5,x0,waste_loop    // back if more delay
    jr      x1                  // return from subroutine
