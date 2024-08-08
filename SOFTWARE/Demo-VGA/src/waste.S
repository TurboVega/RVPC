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

    addi    x8,x0,40          // load delay loop count

waste_loop:

    addi    x8,x8,-1            // decrease count
    bne     x8,x0,waste_loop    // back if more delay
    jr      x1                  // return from subroutine
