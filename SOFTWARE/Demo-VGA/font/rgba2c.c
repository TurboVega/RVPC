#include <stdio.h>

#define _COMPILE_HEX_DATA_
#define __root /**/
#include "font8x8.h"

#define INPUT_BYTES_PER_PIXEL   4
#define INPUT_COLUMNS           16
#define INPUT_ROWS              6
#define CHAR_WIDTH              8
#define CHAR_HEIGHT             8
#define BYTES_PER_INPUT_COLUMN  (CHAR_WIDTH*INPUT_BYTES_PER_PIXEL)
#define BYTES_PER_INPUT_LINE    (INPUT_COLUMNS*BYTES_PER_INPUT_COLUMN)
#define BYTES_PER_INPUT_ROW     (BYTES_PER_INPUT_LINE*CHAR_HEIGHT)

/*
Output character definitions that look similar to this:

#define CHAR_DEF_0x00_0 0b00000000
#define CHAR_DEF_0x00_1 0b00000000
#define CHAR_DEF_0x00_2 0b00000000
#define CHAR_DEF_0x00_3 0b00000000
#define CHAR_DEF_0x00_4 0b00000000
#define CHAR_DEF_0x00_5 0b00000000
#define CHAR_DEF_0x00_6 0b00000000
#define CHAR_DEF_0x00_7 0b00000000
*/

int main() {
    for (int c = 0x00; c < 0x20; c++) {
        if ((c & 0xF) == 0) {
            printf("//--------------------------------\n\n");
        }
        for (int line = 0; line < 8; line++) {
            printf("#define CHAR_DEF_0x%02hX_%hX 0b00000000\n", c, line);
        }
        printf("\n");
    }

    int c = 0x20;
    for (int row=0; row<INPUT_ROWS; row++) {
        for (int col=0; col<INPUT_COLUMNS; col++) {

            if ((c & 0xF) == 0) {
                printf("//--------------------------------\n\n");
            }

            for (int srow=0; srow<CHAR_HEIGHT; srow++) {
                printf("#define CHAR_DEF_0x%02hX_%hX 0b", c, srow);

                for (int scol=0; scol<CHAR_WIDTH; scol++) {
                    int index = (row*BYTES_PER_INPUT_ROW +
                        col*BYTES_PER_INPUT_COLUMN +
                        srow*BYTES_PER_INPUT_LINE +
                        scol*INPUT_BYTES_PER_PIXEL);

                    const unsigned char* p = &gfont8x8_Data[index];

                    if (p[1]) {
                        printf("0");
                    } else {
                        printf("1");
                    }
                }
                printf("\n");
            }
            printf("\n");
            c++;
        }
    }

    for (c = 0x80; c < 0x100; c++) {
        if ((c & 0xF) == 0) {
            printf("//--------------------------------\n\n");
        }
        for (int line = 0; line < 8; line++) {
            printf("#define CHAR_DEF_0x%02hX_%hX 0b00000000\n", c, line);
        }
        printf("\n");
    }
}