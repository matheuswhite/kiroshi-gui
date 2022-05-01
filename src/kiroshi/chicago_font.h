#ifndef __CHICAGO_FONT_H__
#define __CHICAGO_FONT_H__

#include <stdint.h>

struct chicago_font_t {
    uint16_t img[11];
    int width;
    int height;
    int offsety;
};

static int get_index(char sign)
{
    int idx = 0;
    if (sign == '-') {
        idx = 0;
    } else if ('0' <= sign && sign <= '9') {
        idx = sign - '0' + 1;
    } else if ('A' <= sign && sign <= 'Z') {
        idx = sign - 'A' + 1 + 10;
    } else if ('a' <= sign && sign <= 'z') {
        idx = sign - 'a' + 1 + 10 + 26;
    } else if (sign == '%') {
        idx = 63;
    } else if (sign == ':') {
        idx = 64;
    } else {
        idx = -22;
    }

    return idx;
}

static const struct chicago_font_t chicago_font[] = {
    {
        // -
        .img    = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf000, 0x0000, 0x0000, 0x0000,
                0x0000, 0x0000},
        .width  = 4,
        .height = 9,
        .offsety = 0,
    },
    {
        // 0
        .img    = {0x7800, 0xcc00, 0xdc00, 0xdc00, 0xfc00, 0xec00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 1
        .img    = {0x4000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 2,
        .height = 9,
        .offsety = 0,
    },
    {
        // 2
        .img    = {0x7800, 0x8c00, 0x0c00, 0x0c00, 0x1800, 0x3000, 0x6000, 0xc000, 0xfc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 3
        .img    = {0xfc00, 0x1800, 0x3000, 0x7800, 0x0c00, 0x0c00, 0x0c00, 0x8c00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 4
        .img    = {0x0c00, 0x1c00, 0x2c00, 0x4c00, 0xcc00, 0xfe00, 0x0c00, 0x0c00, 0x0c00,
                0x0000, 0x0000},
        .width  = 7,
        .height = 9,
        .offsety = 0,
    },
    {
        // 5
        .img    = {0xfc00, 0xc000, 0xc000, 0xf800, 0x0c00, 0x0c00, 0x0c00, 0x8c00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 6
        .img    = {0x3800, 0x6000, 0xc000, 0xf800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 7
        .img    = {0xfc00, 0x0c00, 0x0c00, 0x1800, 0x1800, 0x3000, 0x3000, 0x3000, 0x3000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 8
        .img    = {0x7800, 0xcc00, 0xcc00, 0xcc00, 0x3000, 0xcc00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // 9
        .img    = {0x7800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x1800, 0x7000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // A
        .img    = {0x7800, 0xcc00, 0xcc00, 0xcc00, 0xfc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // B
        .img    = {0xf800, 0xcc00, 0xcc00, 0xcc00, 0xf000, 0xcc00, 0xcc00, 0xcc00, 0xf800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // C
        .img    = {0x7800, 0xc400, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc400, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // D
        .img    = {0xf800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xf800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // E
        .img    = {0xf800, 0xc000, 0xc000, 0xc000, 0xf000, 0xc000, 0xc000, 0xc000, 0xf800,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // F
        .img    = {0xf800, 0xc000, 0xc000, 0xc000, 0xf000, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // G
        .img    = {0x7800, 0xc400, 0xc000, 0xc000, 0xc300, 0xc000, 0xc000, 0xc000, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // H
        .img    = {0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xfc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // I
        .img    = {0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 2,
        .height = 9,
        .offsety = 0,
    },
    {
        // J
        .img    = {0x0c00, 0x0c00, 0x0c00, 0x0c00, 0x0c00, 0xcc00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // K
        .img    = {0xc400, 0xc800, 0xd000, 0xe000, 0xe000, 0xe000, 0xd000, 0xc800, 0xc400,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // L
        .img    = {0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xf000,
                0x0000, 0x0000},
        .width  = 4,
        .height = 9,
        .offsety = 0,
    },
    {
        // M
        .img    = {0x80c0, 0xc1c0, 0xe3c0, 0xf7c0, 0xbec0, 0x9cc0, 0x88c0, 0x80c0, 0x80c0,
                0x0000, 0x0000},
        .width  = 10,
        .height = 9,
        .offsety = 0,
    },
    {
        // N
        .img    = {0x8200, 0xc200, 0xe200, 0xf200, 0xba00, 0x9e00, 0x8e00, 0x8600, 0x8200,
                0x0000, 0x0000},
        .width  = 7,
        .height = 9,
        .offsety = 0,
    },
    {
        // O
        .img    = {0x7800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // P
        .img    = {0xf800, 0xcc00, 0xcc00, 0xcc00, 0xf800, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // Q
        .img    = {0x7800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7800, 0x0c00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // R
        .img    = {0xf800, 0xcc00, 0xcc00, 0xcc00, 0xfc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // S
        .img    = {0x7000, 0xc800, 0xc000, 0xe000, 0x7000, 0x3800, 0x1800, 0x9800, 0x7000,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // T
        .img    = {0xff00, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800,
                0x0000, 0x0000},
        .width  = 8,
        .height = 9,
        .offsety = 0,
    },
    {
        // U
        .img    = {0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // V
        .img    = {0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xc800, 0xf000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // W
        .img    = {0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xcc80, 0xff00,
                0x0000, 0x0000},
        .width  = 10,
        .height = 9,
        .offsety = 0,
    },
    {
        // X
        .img    = {0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x3000, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // Y
        .img    = {0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7800, 0x3000, 0x3000, 0x3000, 0x3000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // Z
        .img    = {0xfc00, 0x1c00, 0x1800, 0x3800, 0x3000, 0x6000, 0x6000, 0xc000, 0xfc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // a
        .img    = {0x0000, 0x0000, 0x7800, 0x8c00, 0x0c00, 0x7c00, 0xcc00, 0xcc00, 0x7c00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // b
        .img    = {0xc000, 0xc000, 0xf800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xf800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // c
        .img    = {0x0000, 0x0000, 0x7000, 0xc800, 0xc000, 0xc000, 0xc000, 0xc800, 0x7000,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // d
        .img    = {0x0c00, 0x0c00, 0x7c00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7c00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // e
        .img    = {0x0000, 0x0000, 0x7800, 0xcc00, 0xcc00, 0xfc00, 0xc000, 0xc400, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // f
        .img    = {0x3800, 0x6000, 0xf000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // g
        .img    = {0x7c00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x8c00,
                0x7800, 0x0000},
        .width  = 6,
        .height = 10,
        .offsety = 2,
    },
    {
        // h
        .img    = {0xc000, 0xc000, 0xf800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // i
        .img    = {0xc000, 0x0000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 2,
        .height = 9,
        .offsety = 0,
    },
    {
        // j
        .img    = {0x1800, 0x0000, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x9800,
                0x7000, 0x0000},
        .width  = 5,
        .height = 11,
        .offsety = 0,
    },
    {
        // k
        .img    = {0xc000, 0xc000, 0xcc00, 0xd800, 0xf000, 0xc000, 0xf000, 0xd800, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // l
        .img    = {0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 2,
        .height = 9,
        .offsety = 0,
    },
    {
        // m
        .img    = {0x0000, 0x0000, 0xfb80, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xccc0,
                0x0000, 0x0000},
        .width  = 10,
        .height = 9,
        .offsety = 0,
    },
    {
        // n
        .img    = {0x0000, 0x0000, 0xf800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // o
        .img    = {0x0000, 0x0000, 0x7800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7800,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // p
        .img    = {0xf800, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xf800, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 2,
    },
    {
        // q
        .img    = {0x7c00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x0c00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 2,
    },
    {
        // r
        .img    = {0x0000, 0x0000, 0xd800, 0xf800, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // s
        .img    = {0x0000, 0x0000, 0x7000, 0xc800, 0xe000, 0x7000, 0x3800, 0x9800, 0x7000,
                0x0000, 0x0000},
        .width  = 5,
        .height = 9,
        .offsety = 0,
    },
    {
        // t
        .img    = {0x6000, 0x6000, 0xf000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x3000,
                0x0000, 0x0000},
        .width  = 4,
        .height = 9,
        .offsety = 0,
    },
    {
        // u
        .img    = {0x0000, 0x0000, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7c00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // v
        .img    = {0x0000, 0x0000, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xc800, 0xf000,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // w
        .img    = {0x0000, 0x0000, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xccc0, 0xcc80, 0xff00,
                0x0000, 0x0000},
        .width  = 10,
        .height = 9,
        .offsety = 0,
    },
    {
        // x
        .img    = {0x0000, 0x0000, 0xcc00, 0xcc00, 0xcc00, 0x3000, 0xcc00, 0xcc00, 0xcc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // y
        .img    = {0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x8c00,
                0x7800, 0x0000},
        .width  = 6,
        .height = 10,
        .offsety = 2,
    },
    {
        // z
        .img    = {0x0000, 0x0000, 0xfc00, 0x0800, 0x1000, 0x2000, 0x4000, 0xc000, 0xfc00,
                0x0000, 0x0000},
        .width  = 6,
        .height = 9,
        .offsety = 0,
    },
    {
        // %
        // xxoo oxx
        // xxoo xxx
        // ooox xxo

        // ooxx xoo

        // oxxx ooo
        // xxxo oxx
        // xxoo oxx
        .img    = {
            0x0000,
            0x0000,
            0xc600,
            0xce00,
            0x1c00,

            0x3800,

            0x7000,
            0xe600,
            0xc600,
        },
        .width  = 7,
        .height = 9,
        .offsety = 0,
    },
    {
        // :
        // oooo
        // oooo
        // oxxo
        // oxxo
        // oooo
        // oooo
        // oooo
        // oxxo
        // oxxo
        .img    = {
            0x0000,
            0x0000,
            0x6000,
            0x6000,
            0x0000,
            0x0000,
            0x0000,
            0x6000,
            0x6000,
        },
        .width  = 4,
        .height = 9,
        .offsety = 0,
    },
};

#endif  //__CHICAGO_FONT_H__
